#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
using namespace  std;

static std::pair<double, double> mh2ll(const std::string mh)
{
    bool ok;
    double lon = 0.0;
    double lat = 0.0;
    std::vector<u_int8_t> ba2;
    for(char c: mh) {
        ba2.push_back((uint8_t)c);
    }
//    if(ba2.size() == 4) cout<<"ba2 init:"<<ba2.at(0)<<ba2.at(1)<<ba2.at(2)<<ba2.at(3)<<endl;
//    else if(ba2.size() == 6) cout<<"ba2 init:"<<ba2.at(0)<<ba2.at(1)<<ba2.at(2)<<ba2.at(3)<<ba2.at(4)<<ba2.at(5)<<endl;
    // latitude calcs  sample: FM16dw
    int cc2 = ba2.at(1);//.upper().toHex().toInt(&ok, 16);
    if(cc2 > 90) cc2 -= 32; // make upper case
    //cout<<"cc2 init: "<<cc2<<endl;
    cc2 -= 65; // hex of capitol letter of alphabet - 'A' = deg above South pole * 1/10
    cc2 *= 10; // = degrees above zero at South Pole
    // example: M = 120 deg. North of the South pole
    //cout<<"cc2:"<<cc2<<endl;
    int cc4 = atoi((char *)&ba2.at(3));
    //cout<<"cc4:"<<cc4<<" ba2.size():"<<ba2.size()<<endl;
    if(ba2.size() > 4) {
        double cc6 = 0.0;
        cc6 = ba2.at(5); //.toLower().toHex().toInt(&ok, 16);
        if(cc6 < 97) cc6 += 32;
        //cout<<"cc6:"<<cc6<<endl;
        cc6 -= 97.0;
        //cout<<"cc6-1:"<<cc6;
        cc6 /= 24.0;
        //cout<<"cc6-2:"<<cc6;
        cc6 += (1.0/48.0);
        // cout<<"cc6-3:"<<cc6;
        cc6 -= 90;
        //cout<<"cc6-4:"<<cc6;

        lat = (double)cc2 + (double)cc4 + cc6;
    }
    else {
        //cout<<"short version";
        lat = ((double)cc2 - 90) + (double)cc4;
    }

    // end latitude calcs

    // longitude calcs

    int cc1 = ba2.at(0); //.toUpper().toHex().toInt(&ok, 16);
    if(cc1 > 90) cc1 -= 32; // make upper case
    cc1 -= 65;
    cc1 *= 20;

    //cout<<"cc3:"<<ba2.at(2)<<":"<<atoi((char *)&ba2.at(2))<<endl;
    int cc3 = ba2.at(2) - 48;
    cc3*= 2; //.toInt(&ok, 10) * 2;

    if(ba2.size() > 4) {
        double cc5 = 0;
        cc5 = ba2.at(4); //.toLower().toHex().toInt(&ok, 16);
        if(cc5 < 97) cc5 += 32;// make lower case
        cc5 -= 97.0;
        cc5 /= 12.0;
        cc5 += (1.0/24.0);
        lon = ((double)cc1 + (double) cc3 + cc5) - 180.0;
    }
    else {
        lon = (double)cc1 + (double)cc3 - 180.0;
    }
    // end longitude calcs

    //cout<<"lat:"<<lat<<endl;
    //cout<<cc1<<cc3;
    //cout<<"lon:"<<lon<<endl;
    return std::pair<double, double>(lat, lon);
}