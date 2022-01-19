FieldLab C Programming project

Project Description:

-The FieldLab C Programming project is meant to convert the existing Python code that is used for sending data from the RobotStudio software to the database, 
to a more efficient and faster C++ implementation.


Goals of the Project:

-Translate Python code to C++


Current Status: Program polls Nodes from an OPC UA Server and sends data to a PostgreSQL database

Project Dependencies  
https://github.com/open62541/open62541  
Used open62541 version 1.2 single file release  
https://github.com/jtv/libpqxx  
Used libpqxx version 7.3.1  


CREATING A CERTIFICATE AND KEY


Make a .txt file with the following:  



[ req ]  
default_bits = 2048  
default_md = sha256  
distinguished_name = subject  
req_extensions = req_ext  
x509_extensions = req_ext  
string_mask = utf8only  
prompt = no  
[ req_ext ]  
basicConstraints = CA:FALSE  
nsCertType = client, server  
keyUsage = nonRepudiation, digitalSignature, keyEncipherment, dataEncipherment, keyCertSign  
extendedKeyUsage= serverAuth, clientAuth  
nsComment = "Certificate for Open62541 OPC UA C++ Client"  
subjectKeyIdentifier=hash  
authorityKeyIdentifier=keyid,issuer  
subjectAltName = URI:urn:opcua:Cplusplus:client,IP: 127.0.0.1  
[ subject ]  
countryName = FI  
stateOrProvinceName = FI  
localityName = FI  
organizationName = ABB  
commonName = CplusplusOpcUaClient  



You can change the settings but subjectAltName has to match the set client config applicationUri exactly.  
(with the above settings it would be "urn:opcua:Cplusplus:client")  
Name the .txt file to cert.conf  

open powershell as admin  
enter openssl in powershell  
enter "genrsa -out YourPath\opcuaclient.key.pem 2048", where YourPath is the location of the files  
enter "req -x509 -days 365 -new -out YourPath\cert.pem -key YourPath\opcuaclient.key.pem -config YourPath\cert.conf", where YourPath is the location of the files  
enter "x509 -outform der -in YourPath\cert.pem -out YourPath\opcuaclientcert.der", where YourPath is the location of the files  
When the files are generated, place the opcuaclientcert.der and opcuaclient.key.pem in the same directory as the client executable


INSTALLING AND USING VCPKG (if the provided pqxx.lib file does not work)

installation instructions  
https://github.com/Microsoft/vcpkg  

open powershell as admin  
navigate to the directory you have installed vcpkg  
enter ".\vcpkg install libpqxx:x86-windows-static"  
in Visual Studio project properties  
Linker -> General -> Additional Library Directories -> add path to the "YOURPATH\vcpkg\packages\libpqxx_x86-windows-static\lib" directory  
Linker -> Input -> Additional Dependencies -> add "pqxx.lib"  

CHANGING THE SERVER OR DATABASE ADDRESS  

To change the address of the server the client connects to, change the endpointUrl variable ("opc.tcp://IP:PORT/ABB.IRC5.OPCUA.Server" was used in testing)  

To change the database the client connects to, change the Co variable  
To connect to the database you will need the database name, the username, the password for the user and the host ip address and port.  

To change the table the data is inserted to, make changed to the Co.prepare functions SQL statement ("INSERT INTO gen5_copy() was used in testing)  
