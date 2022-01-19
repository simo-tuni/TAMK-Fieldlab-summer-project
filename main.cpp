 /*
 This OPC UA Client uses Open62541 open source library to pull nodes from an OPC UA Server (ABB IRC5 OPC UA Server was used in testing)
 and Libpqxx open source library to send data to the PostgreSQL database
 Nodes are configured in Setup_abb.h file. (36 nodes were used in testing)
 To run the program ensure that the OPC UA Server is running, the robot the server is connected to is running
 and that the certificate and key files are located in the same directory as the executable.
 */

/*
Changes to open62541.h:
*if you need more debug info prints, set UA_LOGLEVEL from 300 to 100 in open62541.h (300 was used in testing)
*set "#define UA_ENABLE_ENCRYPTION" from "#undef UA_ENABLE_ENCRYPTION", to use encryption features like UA_ClientConfig_setDefaultEncryption()
*set "#define UA_ENABLE_ENCRYPTION_OPENSSL" from "#undef UA_ENABLE_ENCRYPTION_OPENSSL", to use openssl
*/

/*
Settings in
Visual Studio 2019 project properties
General -> C++ Language Standard -> ISO C++ 17 Standard
vcpkg -> Use Static Libraries -> Yes
C/C++ -> Preprocessor -> Preprocessor Definitions -> add "NDEBUG" "_CRT_SECURE_NO_WARNINGS"
C/C++ -> Code Generation -> Runtime Library -> Multi-threaded (/MT)
C/C++ -> Language -> C++ Language Standard -> ISO C++ 17 Standard
Linker -> General -> Additional Library Directories -> add path to the directory pqxx.lib is in
Linker -> Input -> Additional Dependencies -> add "pqxx.lib"
*/



#include <stdlib.h>                 //Standard library
#include <iostream>                 //Standard library

#include "pqxx/connection.hxx"      //Included using vcpkg
#include "pqxx/transaction.hxx"     //Included using vcpkg
#include "open62541.h"              //Including the Open62541 library
#include "common.h"                 //Including code to load the Security Certificate (*.der) and the Key (*.pem)
#include "Setup_abb.h"              //Prototype sensor table
#include "Setup_db.h"               //Prototype db settings

//Include libraries needed to run on windows
#pragma comment(lib, "ws2_32.lib")
#pragma comment (lib, "crypt32")
#pragma comment(lib, "secur32.lib")


int main() {
    //Begin
    
    Sensor_table sens;      //Create a Sensor_table
    db_table db_default;    //database settings
    

    Sensor_table_initialize(&sens);     //Initialize sens array with data from the "Setup_abb.py" file

    const char* endpointUrl = "opc.tcp://########/ABB.IRC5.OPCUA.Server";    //Set the server url

    int nullCheck = 0;     //Variable to check that certificate and key are opened (they exist and are in the correct directory)
                           //If not this is set to 1 in loadFile function and the program exits

    UA_ByteString certificate = loadFile("opcuaclientcert.der", nullCheck);      //Load Security Certificate
    UA_ByteString privateKey = loadFile("opcuaclient.key.pem", nullCheck);       //Load the Key
    if (nullCheck == 1) {                                                        //Check that cert and key were loaded 
        do
        {
            std::cout << '\n' << "Failed to read certificate or key, press enter to exit program...";
        } while (std::cin.get() != '\n');
        return EXIT_FAILURE;
    }

    size_t trustListSize = 0;               //We do not use trustList as far as i know, but it still needs to exist
    UA_ByteString* trustList = NULL;        //We do not use trustList as far as i know, but it still needs to exist

    UA_ByteString* revocationList = NULL;   //We do not use revocationList as far as i know, but it still needs to exist
    size_t revocationListSize = 0;          //We do not use revocationList as far as i know, but it still needs to exist

    UA_Client* client = UA_Client_new();                                //Create a new UA_Client named client
    UA_ClientConfig* cc = UA_Client_getConfig(client);                  //Create a new client config named cc
    UA_ClientConfig_setDefaultEncryption(cc, certificate, privateKey,   //Set client config to use the default encryption settings (we modify these settings afterwards)
        trustList, trustListSize,
        revocationList, revocationListSize);

    cc->clientDescription.applicationUri = UA_STRING_ALLOC("urn:opcua:Cplusplus:client");  //Set the applicationUri, this has to match the Security Certificate

    cc->securityPolicyUri = UA_STRING_ALLOC("http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256");   //Set security policy to Basic256Sha256

    UA_ByteString_clear(&certificate);      //Clear variable
    UA_ByteString_clear(&privateKey);       //Clear variable
    for (size_t deleteCount = 0; deleteCount < trustListSize; deleteCount++) {      //Delete trustlist, it was size 0 and NULL so this may not even do anything
        UA_ByteString_clear(&trustList[deleteCount]);
    }

    /* Secure client connect */
    cc->securityMode = UA_MESSAGESECURITYMODE_SIGNANDENCRYPT; /* require encryption */
    UA_StatusCode retval = UA_Client_connect(client, endpointUrl);      //Connect the Client to the Server
    if (retval != UA_STATUSCODE_GOOD) {         //If Client fails to connect to the server it enters this, deletes client and exits the program
        UA_Client_delete(client);
        do
        {
            std::cout << '\n' << "Failed to connect to the server, press enter to exit program...";
        } while (std::cin.get() != '\n');
        return EXIT_FAILURE;
    }

    UA_Variant value;           //Create a new UA_Variant variable
    UA_Variant_init(&value);    //Initialize the variable

    UA_LocalizedText Node_displayname;                                          //Create new UA_LocalizedText variable (needed by UA_Client_readDisplayNameAttribute)
    UA_LocalizedText_init(&Node_displayname);                                   //Initialize variable

    UA_ReadRequest request;                                                     //Using ReadRequest to read 36 nodes at once
    UA_ReadRequest_init(&request);                                              //Initialize (mandatory)
    UA_ReadValueId ids[NODE_AMOUNT];                                                     //Set how many ids we read
    for (int i = 0; i < NODE_AMOUNT; i++) {                                             //Initialize ids and set nodeId
        UA_ReadValueId_init(&ids[i]);
        ids[i].attributeId = UA_ATTRIBUTEID_VALUE;
        ids[i].nodeId = UA_NODEID_NUMERIC(sens.i_node[i], sens.ns_node[i]);
    }

    request.nodesToRead = ids;      //Connect nodes to the request
    request.nodesToReadSize = NODE_AMOUNT;   //Set request size

    for (int i = 0; i < NODE_AMOUNT; i++) {                                                         //Read and save node display name
        UA_NodeId nodeIdName = UA_NODEID_NUMERIC(sens.i_node[i], sens.ns_node[i]);          //Set nodeId
        retval = UA_Client_readDisplayNameAttribute(client, nodeIdName, &Node_displayname); //Read the name of the Node

        if (retval == UA_STATUSCODE_GOOD) {                                                 //If the read was successful print the name
            UA_String Node_name = Node_displayname.text;
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Retrieved %.*s from server\n", Node_name); //Print
            char* convert = (char*)UA_malloc(sizeof(char) * Node_name.length + 1);  //Convert node name from UA_String to char*
            memcpy(convert, Node_name.data, Node_name.length);                      //Convert node name from UA_String to char*
            convert[Node_name.length] = '\0';                                       //Convert node name from UA_String to char*
            sens.node_name[i] = convert;                                            //Save node name to Sensor_table
        }
        UA_LocalizedText_clear(&Node_displayname);                                  //Clear and reinitialize for next loop
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server read loop\n"); //Output message for user
    while (true) {                                                                      //Begin pull->send loop that goes on until the program is shut down or the connection fails

                                                                                        //TODO: make the client automatically reconnect to the OPC UA Server and Postgresql database in the event of disconnection

        UA_ReadResponse response = UA_Client_Service_read(client, request);         //Read all 36 nodes at once and then print the values
        pqxx::connection Co("dbname = ######## user = ######## password = ######## \ hostaddr = ######## port = ########");                   //Connect to the database
        pqxx::transaction txn(Co, "In");              //Prepare transaction
                                                      //Prepare SQL command
        Co.prepare("In", "INSERT INTO gen5_copy(  \
                            city,                 \
                            place,                \
                            machine,              \
                            machine_type,         \
                            machine_number,       \
                            machine_module,       \
                            meas_name,            \
                            signal_name,          \
                            signal_number,        \
                            signal_value,         \
                            signal_unit,          \
                            signal_value_type,    \
                            time_stamp            \
                        )                         \
                        VALUES (                  \
                            $1,                   \
                            $2,                   \
                            $3,                   \
                            $4,                   \
                            $5,                   \
                            $6,                   \
                            $7,                   \
                            $8,                   \
                            $9,                   \
                            $10,                  \
                            $11,                  \
                            $12,                  \
                            NOW()::timestamptz(3) \
                        )"
        );
        for (int i = 0; i < NODE_AMOUNT; i++) {     //Looping and sending 36 rows at once to speed database operations
            try {
                if (Co.is_open()) {         //If connection to the database is open
                                            //Execute prepared SQL command
                    txn.exec_prepared("In",
                        db_default.city,
                        db_default.place,
                        db_default.machine,
                        db_default.machine_type,
                        db_default.machine_number,
                        db_default.machine_module,
                        "ABB Meas 1",
                        sens.node_name[i],
                        1,
                        *(UA_Double*)response.results[i].value.data,
                        sens.unit[i],
                        sens.type[i]
                    );                      
                }
                else {                                                                                                          //If connection is not active, exit program
                    do
                    {
                        std::cout << '\n' << "ERROR: Connection to database severed, press enter to exit program...";
                    } while (std::cin.get() != '\n');
                    return EXIT_FAILURE;
                }
            }
            catch (const std::exception& e) {                                                                                  //Catch exception, print it and exit program
                std::cerr << e.what() << std::endl;
                do
                {
                    std::cout << '\n' << "Failed to connect to the database, press enter to exit program...";
                } while (std::cin.get() != '\n');
                return EXIT_FAILURE;
            }
        }
        txn.commit();                                                                                       //Commit changes to database
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Committed changes to the database\n");         //Output message for user
    }
    /* Clean up */
    UA_Variant_clear(&value);
    UA_Client_delete(client);
    do
    {
        std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
