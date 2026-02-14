#pragma once
#include <map>

class World;
class GameObject;
class Action;
enum class ActionType;
class State;

enum class StateType {Standing, InAir};
enum class Transition {Jump, Stop};

using Transitions = std::map<std::pair<StateType, Transition>, StateType>;
using States = std::map<StateType, State*>;

class FSM {
};