//
// Created by benji on 26/11/16.
//

#include "Rules.h"

Rules::Rules(RuleDefinition rule) {
    loadRule(rule);
}

void Rules::add(std::string color, Move rule) {
    Color c(color);
    add(c, rule);
}

void Rules::add(Color color, Move rule) {
    bool existingColor = false;
    for(unsigned int i = 0 ; i < _listRules.size() ; i++) {
        if(color == _listRules[i].first)
            existingColor = true;
    }

    if(!existingColor)
        _listRules.push_back({color, rule});
    else
        std::cerr << _RED("Warning : the color '" + color.getColorName() + "' already exists.") << std::endl;
}

void Rules::reset() {
    _listRules.clear();
}

void Rules::loadRule(RuleDefinition ruleDefinition) {
    reset();

    for(int i = 0 ; i < ruleDefinition.size() ; i++) {
        add(ruleDefinition.color(i), ruleDefinition.move(i));
    }
}

std::vector<Color> Rules::getListColors() {
    std::vector<Color> result;

    for(unsigned int i = 0 ; i < _listRules.size() ; i++) {
        result.push_back(_listRules[i].first);
    }
    return result;
}

Orientation Rules::getNewOrientation(Orientation currentOrientation, Color cubeColor) {
    Move move = getRule(cubeColor);
    if(move == Move::DO_NOTHING)
        return currentOrientation;
    return ORIENTATION_CHANGES[(int)move][(int)currentOrientation];
}

Move Rules::getRule(Color color) {
    for(unsigned int i = 0 ; i < _listRules.size() ; i++) {
        if(color == _listRules[i].first)
            return _listRules[i].second;
    }
    std::cerr << _RED("Unexisting rule color") << std::endl;
    return DO_NOTHING;
}

Color Rules::nextColor(Color color) {
    if(color == AllColors::NULL_COLOR)
        return AllColors::NULL_COLOR;

    for(unsigned int i = 0 ; i < _listRules.size() - 1 ; i++) {
        if(color == _listRules[i].first)
            return _listRules[i+1].first;
    }
    return Color(_listRules[0].first);
}

std::string Rules::getRules() {
    std::string rules;
    std::string color;
    unsigned int sizeMax = 0;
    for(unsigned int i = 0 ; i < _listRules.size() ; i++) {
        if(_listRules[i].first.getColorName().size() > sizeMax)
            sizeMax = (int)_listRules[i].first.getColorName().size();
    }

    for(unsigned int i = 0 ; i < _listRules.size() ; i++) {
        color = _listRules[i].first.getColorName();
        rules += color;
        for(unsigned int k = 0 ; k < sizeMax - color.size() ; k++)
            rules += ' ';
        rules += " : " + getMoveName(_listRules[i].second) + "\n";
    }

    return rules;
}

Orientation Rules::getInitOrientation() {
    switch(_listRules[0].second) {
        case Move::GO_FRONT: return UP;
        case Move::GO_BACK:  return DOWN;
        case Move::GO_UP:    return RIGHT;
        case Move::GO_DOWN:  return LEFT;
        case Move::GO_RIGHT: return FRONT;
        case Move::GO_LEFT:  return BACK;
        default: return FRONT; // Move::DO_NOTHING
    }
}

std::string Rules::getMoveName(Move move) {
    switch(move) {
        case Move::GO_FRONT:   return "GO_front";
        case Move::GO_BACK:    return "GO_back";
        case Move::GO_RIGHT:   return "GO_right";
        case Move::GO_LEFT:    return "GO_left";
        case Move::GO_UP:      return "GO_up";
        case Move::GO_DOWN:    return "GO_down";
        default:/*case Move::DO_NOTHING:*/ return "do nothing";
    }
}

std::string Rules::getOrientationName(Orientation orientation) {
    switch(orientation) {
        case Orientation::FRONT:   return "front";
        case Orientation::BACK:    return "back";
        case Orientation::RIGHT:   return "right";
        case Orientation::LEFT:    return "left";
        case Orientation::UP:      return "up";
        case Orientation::DOWN:    return "down";
        default: std::cerr << "ERROR" << std::endl; return "front";
    }
}