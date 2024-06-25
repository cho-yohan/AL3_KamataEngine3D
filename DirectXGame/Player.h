#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MathUtilityForText.h"

enum class LRDirection {
	kRight,
	kLeft,
};

class Player { 
public: 
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 5;
	static inline const float kAttenuation = 2;
	static inline const float kLimitRunSpeed = 4;

	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	static inline const float kTimeTurn = 0.3f;

	//接地状態フラグ
	bool onGround_ = true;
	// 着地フラグ
	bool landing;

	//重力加速度 (下方向)
	static inline const float kGravityAcceleration = 3;
	//最大落下速度 (下方向)
	static inline const float kLimitFallSpeed = 3;
	//ジャンプ初速 (上方向)
	static inline const float kJumpAcceleration = 3;
};