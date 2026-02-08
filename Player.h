#pragma once
#include <raylib.h>
#include <raymath.h>

class Player;
class PlayerState {
    public:
        virtual ~PlayerState() = default;

        virtual void Enter(Player& player) {}
        virtual void Update(Player& player, float delta_time) = 0;
        virtual void Exit(Player& player) {}
};

class IdleState : public PlayerState {
    public:
        void Enter(Player& player) override; // Enter the state
        void Update(Player& player, float delta_time) override;
            // Code that performs every frame
            // Has the code that transitions state
            // Can transition to Moving using WASD
            // Can transition to Attacking using Left Mouse Button
            // Can transition to Blocking using Right Mouse Button
};

class MovingState : public PlayerState {
    public:
        void Enter(Player& player) override; // Enter the state
        void Update(Player& player, float delta_time) override;
            // Moves character
            // Transitions to Idle when movement stops
            // Can transition to Dodging using Space button
            // Can transition to Attacking using Left Mouse Button
};

class AttackingState : public PlayerState {
    private:
        float attack_timer = 0.0f;
        const float attack_duration = 0.5f;
    
    public:
        void Enter(Player& player) override;
            // Enter the state
            // Set active time of Attack
        void Update(Player& player, float delta_time) override;
            // Count down from active time
            // Transitions to Idle when count down ends
};

class BlockingState : public PlayerState {
    public:
        void Enter(Player& player) override; // Enter the state
        void Update(Player& player, float delta_time) override;
            // As long as RMB is held, remmain in Blocking
            // Player cannot move
            // Return to Idle when RMB is released
};

class DodgingState : public PlayerState {
    private:
        float dodge_timer = 0.0f;
        const float dodge_duration = 0.3f;
        const float dodge_speed = 2.3f;
        Vector2 dodge_direction = {0,0};

    public:
        void Enter(Player& player) override; // Enter the state
        void Update(Player& player, float delta_time) override;
            // Moves character a fair distance quickly
            // Transitions to Idle when movement stops
};

class StateMachine {
    private:
        PlayerState* currentState = nullptr;
        
    public:
        void SetState(PlayerState* s, Player& player);
        void UpdateState(Player& player, float delta_time);
};
class Player {
    private:
        Vector2 position;
        float radius;
        float speed;
        Color color;

        StateMachine stateMachine;

        IdleState* idle;
        MovingState* moving;
        AttackingState* attacking;
        BlockingState* blocking;
        DodgingState* dodging;
    
    public:
        Player(Vector2 startPosition);
        ~Player();

        void Update(float delta_time);
        void Draw() const;

        void SetColor (Color c);
        Color GetColor() const;

        void ChangeState(PlayerState* newState);

        Vector2 GetPosition() const;
        void SetPosition(Vector2 newPosition);

        float GetSpeed() const;

        PlayerState* GetIdleState() {return idle;}
        PlayerState* GetMovingState() {return moving;}
        PlayerState* GetAttackingState() {return attacking;}
        PlayerState* GetBlockingState() {return blocking;}
        PlayerState* GetDodgingState() {return dodging;}
};


