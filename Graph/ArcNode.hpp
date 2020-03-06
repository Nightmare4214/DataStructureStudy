#pragma once

#include <cstring>
//边点
class ArcNode{
public:
    int weight;
    size_t adj_vex;
    ArcNode* next;
    ArcNode():weight(0x3f3f3f3f),adj_vex(0),next(nullptr){}
    ArcNode(const size_t& adj_vex,const int& weight):weight(0x3f3f3f3f),adj_vex(0),next(nullptr){}
};
