#pragma once

enum class ActionType {
    None,
    Jump,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    MoveUpLeft,
    MoveUpRight,
    MoveDownLeft,
    MoveDownRight,
    Sprint,
    Decelerate
};

class World;
class GameObject;

class Action {
public:
    virtual ~Action() = default;
    virtual void perform(World& world, GameObject& obj) = 0;
};

class Jump : public Action {
    void perform(World &world, GameObject& obj) override;
};

class MoveRight : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveLeft : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveUp : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveDown : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveUpLeft : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveUpRight : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveDownLeft : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveDownRight : public Action {
    void perform(World&, GameObject& obj) override;
};

class Sprint : public Action {
    void perform(World&, GameObject& obj) override;
};

class Decelerate : public Action {
    void perform(World&, GameObject& obj) override;
};