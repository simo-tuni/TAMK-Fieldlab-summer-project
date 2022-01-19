#pragma once
#include <string>
#include "open62541.h"

const int NODE_AMOUNT = 36;     //Set the amount of nodes that are read

struct Sensor_table {
    int ns_node[NODE_AMOUNT];
    int i_node[NODE_AMOUNT];
    std::string unit[NODE_AMOUNT];
    int s_number[NODE_AMOUNT];
    std::string type[NODE_AMOUNT];

    std::string node_name[NODE_AMOUNT];
};

//Settings from Setup_abb.py

void Sensor_table_initialize(Sensor_table* sens) {

    sens->i_node[0] = 2;        //positionAxis1
    sens->ns_node[0] = 396;
    sens->unit[0] = "Deg";
    sens->s_number[0] = 1;
    sens->type[0] = "Num";

    sens->i_node[1] = 2;        //positionAxis2
    sens->ns_node[1] = 382;
    sens->unit[1] = "Deg";
    sens->s_number[1] = 1;
    sens->type[1] = "Num";

    sens->i_node[2] = 2;        //positionAxis3
    sens->ns_node[2] = 371;
    sens->unit[2] = "Deg";
    sens->s_number[2] = 1;
    sens->type[2] = "Num";

    sens->i_node[3] = 2;        //positionAxis4
    sens->ns_node[3] = 404;
    sens->unit[3] = "Deg";
    sens->s_number[3] = 1;
    sens->type[3] = "Num";

    sens->i_node[4] = 2;        //positionAxis5
    sens->ns_node[4] = 387;
    sens->unit[4] = "Deg";
    sens->s_number[4] = 1;
    sens->type[4] = "Num";

    sens->i_node[5] = 2;        //positionAxis6
    sens->ns_node[5] = 373;
    sens->unit[5] = "Deg";
    sens->s_number[5] = 1;
    sens->type[5] = "Num";

    // Unit change

    sens->i_node[6] = 2;        //speedAxis1
    sens->ns_node[6] = 397;
    sens->unit[6] = "Deg/s";
    sens->s_number[6] = 1;
    sens->type[6] = "Num";

    sens->i_node[7] = 2;        //speedAxis2
    sens->ns_node[7] = 375;
    sens->unit[7] = "Deg/s";
    sens->s_number[7] = 1;
    sens->type[7] = "Num";

    sens->i_node[8] = 2;        //speedAxis3
    sens->ns_node[8] = 398;
    sens->unit[8] = "Deg/s";
    sens->s_number[8] = 1;
    sens->type[8] = "Num";

    sens->i_node[9] = 2;        //speedAxis4
    sens->ns_node[9] = 376;
    sens->unit[9] = "Deg/s";
    sens->s_number[9] = 1;
    sens->type[9] = "Num";

    sens->i_node[10] = 2;        //speedAxis5
    sens->ns_node[10] = 399;
    sens->unit[10] = "Deg/s";
    sens->s_number[10] = 1;
    sens->type[10] = "Num";

    sens->i_node[11] = 2;        //speedAxis6
    sens->ns_node[11] = 377;
    sens->unit[11] = "Deg/s";
    sens->s_number[11] = 1;
    sens->type[11] = "Num";

    // Unit change

    sens->i_node[12] = 2;       //TorqueAxis1
    sens->ns_node[12] = 394;
    sens->unit[12] = "Nm";
    sens->s_number[12] = 1;
    sens->type[12] = "Num";

    sens->i_node[13] = 2;       //TorqueAxis2
    sens->ns_node[13] = 411;
    sens->unit[13] = "Nm";
    sens->s_number[13] = 1;
    sens->type[13] = "Num";

    sens->i_node[14] = 2;       //TorqueAxis3
    sens->ns_node[14] = 386;
    sens->unit[14] = "Nm";
    sens->s_number[14] = 1;
    sens->type[14] = "Num";

    sens->i_node[15] = 2;       //TorqueAxis4
    sens->ns_node[15] = 407;
    sens->unit[15] = "Nm";
    sens->s_number[15] = 1;
    sens->type[15] = "Num";

    sens->i_node[16] = 2;       //TorqueAxis5
    sens->ns_node[16] = 381;
    sens->unit[16] = "Nm";
    sens->s_number[16] = 1;
    sens->type[16] = "Num";

    sens->i_node[17] = 2;       //TorqueAxis6
    sens->ns_node[17] = 402;
    sens->unit[17] = "Nm";
    sens->s_number[17] = 1;
    sens->type[17] = "Num";

    // Unit change

    sens->i_node[18] = 2;       //MaxTorqueAxis1
    sens->ns_node[18] = 393;
    sens->unit[18] = "Nm Max";
    sens->s_number[18] = 1;
    sens->type[18] = "Num";

    sens->i_node[19] = 2;       //MaxTorqueAxis2
    sens->ns_node[19] = 410;
    sens->unit[19] = "Nm Max";
    sens->s_number[19] = 1;
    sens->type[19] = "Num";

    sens->i_node[20] = 2;       //MaxTorqueAxis3
    sens->ns_node[20] = 385;
    sens->unit[20] = "Nm Max";
    sens->s_number[20] = 1;
    sens->type[20] = "Num";

    sens->i_node[21] = 2;       //MaxTorqueAxis4
    sens->ns_node[21] = 406;
    sens->unit[21] = "Nm Max";
    sens->s_number[21] = 1;
    sens->type[21] = "Num";

    sens->i_node[22] = 2;       //MaxTorqueAxis5
    sens->ns_node[22] = 380;
    sens->unit[22] = "Nm Max";
    sens->s_number[22] = 1;
    sens->type[22] = "Num";

    sens->i_node[23] = 2;       //MaxTorqueAxis6
    sens->ns_node[23] = 401;
    sens->unit[23] = "Nm Max";
    sens->s_number[23] = 1;
    sens->type[23] = "Num";

    // Unit change

    sens->i_node[24] = 2;       //AvgTorqueAxis1
    sens->ns_node[24] = 392;
    sens->unit[24] = "Nm Avg";
    sens->s_number[24] = 1;
    sens->type[24] = "Num";

    sens->i_node[25] = 2;       //AvgTorqueAxis2
    sens->ns_node[25] = 409;
    sens->unit[25] = "Nm Avg";
    sens->s_number[25] = 1;
    sens->type[25] = "Num";

    sens->i_node[26] = 2;       //AvgTorqueAxis3
    sens->ns_node[26] = 384;
    sens->unit[26] = "Nm Avg";
    sens->s_number[26] = 1;
    sens->type[26] = "Num";

    sens->i_node[27] = 2;       //AvgTorqueAxis4
    sens->ns_node[27] = 405;
    sens->unit[27] = "Nm Avg";
    sens->s_number[27] = 1;
    sens->type[27] = "Num";

    sens->i_node[28] = 2;       //AvgTorqueAxis5
    sens->ns_node[28] = 379;
    sens->unit[28] = "Nm Avg";
    sens->s_number[28] = 1;
    sens->type[28] = "Num";

    sens->i_node[29] = 2;       //AvgTorqueAxis6
    sens->ns_node[29] = 400;
    sens->unit[29] = "Nm Avg";
    sens->s_number[29] = 1;
    sens->type[29] = "Num";

    // Unit change

    sens->i_node[30] = 2;       //PositionTrack
    sens->ns_node[30] = 383;
    sens->unit[30] = "mm";
    sens->s_number[30] = 1;
    sens->type[30] = "Num";

    // Unit change

    sens->i_node[31] = 2;       //TorqueTrack
    sens->ns_node[31] = 391;
    sens->unit[31] = "Nm";
    sens->s_number[31] = 1;
    sens->type[31] = "Num";

    sens->i_node[32] = 2;       //TorqueMaxTrack
    sens->ns_node[32] = 390;
    sens->unit[32] = "Nm";
    sens->s_number[32] = 1;
    sens->type[32] = "Num";

    sens->i_node[33] = 2;       //TorqueAvgTrack
    sens->ns_node[33] = 389;
    sens->unit[33] = "Nm";
    sens->s_number[33] = 1;
    sens->type[33] = "Nnum";

    // Unit change

    sens->i_node[34] = 2;       //Printing time
    sens->ns_node[34] = 408;
    sens->unit[34] = "s";
    sens->s_number[34] = 1;
    sens->type[34] = "Num";

    // Unit change

    sens->i_node[35] = 2;       //TCP position
    sens->ns_node[35] = 395;
    sens->unit[35] = "xyz";
    sens->s_number[35] = 1;
    sens->type[35] = "Pos";

}