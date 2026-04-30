#pragma once

enum class ActionType {
    None,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    MoveUpLeft,
    MoveUpRight,
    MoveDownLeft,
    MoveDownRight,
    Sprint,
    AttackAll
};

class World;
class GameObject;

class Action {
public:
    virtual ~Action() = default;
    virtual void perform(World& world, GameObject& obj) = 0;
};

class MoveRight : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveLeft : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveUp : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveDown : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveUpLeft : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveUpRight : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveDownLeft : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class MoveDownRight : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class Sprint : public Action {
public:
    void perform(World&, GameObject& obj) override;
};

class AttackAll : public Action {
public:
    void perform(World&, GameObject &obj) override;
};

class AttackRight : public Action {
public:
    void perform(World& world, GameObject& obj) override;
};

class AttackLeft : public Action {
public:
    void perform(World& world, GameObject& obj) override;
};

class AttackUp : public Action {
public:
    void perform(World& world, GameObject& obj) override;
};

class ShootArrow : public Action {
public:
    void perform(World& world, GameObject& obj) override;
};