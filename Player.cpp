#include "Player.hpp"

Player::Player(Vector2 startPosition) {
    position = startPosition;
    radius = 40.0f;
    speed = 200.0f;
    color = ORANGE;

    idle = new IdleState();
    moving = new MovingState();
    attacking = new AttackingState();
    blocking = new BlockingState();
    dodging = new DodgingState();

    stateMachine.SetState(idle, *this);
}

Player::~Player() {
    delete idle;
    delete moving;
    delete attacking;
    delete blocking;
    delete dodging;
};

void Player::Update(float delta_time) {
    stateMachine.UpdateState(*this, delta_time);
}

void Player::Draw() const {
    DrawCircleV(position, radius, color);
}

void Player::SetColor(Color c) {
    color = c;
}

Color Player::GetColor() const {
    return color;
}

void Player::ChangeState(PlayerState* newState) {
    stateMachine.SetState(newState, *this);
}

Vector2 Player::GetPosition() const {
    return position;
}

void Player::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

float Player::GetSpeed() const {
    return speed;
}

void StateMachine::SetState(PlayerState* s, Player& player) {
    if (currentState != nullptr) {
        currentState->Exit(player);
    }

    currentState = s;

    if (currentState != nullptr) {
        currentState->Enter(player);
    }
}

void StateMachine::UpdateState(Player& player, float delta_time) {
    if (currentState != nullptr) {
        currentState->Update(player, delta_time);
    }
}

void IdleState::Enter(Player& player) {
    player.SetColor(ORANGE);
}

void IdleState::Update(Player& player, float delta_time) {
    bool isMoving = IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D);

    if (isMoving) {
        player.ChangeState(player.GetMovingState());
        return;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        player.ChangeState(player.GetAttackingState());
        return;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        player.ChangeState(player.GetBlockingState());
        return;
    }
}

void MovingState::Enter(Player& player) {
    player.SetColor(YELLOW);
}

void MovingState::Update(Player& player, float delta_time) {
    bool isMoving = IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        player.ChangeState(player.GetAttackingState());
        return;
    }
    
    if (IsKeyPressed(KEY_SPACE)) {
        player.ChangeState(player.GetDodgingState());
        return;
    }

    if (!isMoving) {
        player.ChangeState(player.GetIdleState());
        return;
    }
    
    Vector2 pos = player.GetPosition();
    float speed = player.GetSpeed();
    
    Vector2 direction = {0, 0};
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;

    if (direction.x != 0 || direction.y != 0) {
        direction = Vector2Normalize(direction);
    }
    pos.x += direction.x * speed * delta_time;
    pos.y += direction.y * speed * delta_time;
    
    player.SetPosition(pos);
}

void AttackingState::Enter(Player& player) {
    attack_timer = attack_duration;
    player.SetColor(MAROON);
}

void AttackingState::Update(Player& player, float delta_time) {
    attack_timer -= delta_time;
    
    if (attack_timer <= 0.0f) {
        player.ChangeState(player.GetIdleState());
        return;
    }
}

void BlockingState::Enter(Player& player) {
    player.SetColor(BLACK);
}

void BlockingState::Update(Player& player, float delta_time) {
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        player.ChangeState(player.GetIdleState());
        return;
    }
}

void DodgingState::Enter(Player& player) {
    player.SetColor(MAGENTA);
    dodge_timer = dodge_duration;
    
    dodge_direction = {0,0};
    if (IsKeyDown(KEY_W)) dodge_direction.y -= 1; 
    if (IsKeyDown(KEY_A)) dodge_direction.x -= 1; 
    if (IsKeyDown(KEY_S)) dodge_direction.y += 1; 
    if (IsKeyDown(KEY_D)) dodge_direction.x += 1; 

    if (dodge_direction.x != 0 || dodge_direction.y != 0) {
        dodge_direction = Vector2Normalize(dodge_direction);
    } else {
        dodge_direction = {-1,0}; // Default dodge is to the left
    }
}

void DodgingState::Update(Player& player, float delta_time) {
    dodge_timer -= delta_time;

    if (dodge_timer > 0) {
        Vector2 pos = player.GetPosition();
        pos.x += dodge_direction.x * (player.GetSpeed() * dodge_speed) * delta_time;
        pos.y += dodge_direction.y * (player.GetSpeed() * dodge_speed) * delta_time;
        player.SetPosition(pos);
    } else {
        player.ChangeState(player.GetIdleState());
        return;
    }
}