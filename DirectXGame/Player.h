#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "myMath.h"

class MapChipField;

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};

	// 角
	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner // 要素数
	};

	/// <summary>
	/// 初期化
	/// </summary>
	//	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);
	void Initialize(const Vector3& position, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// setter
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	
	// getter
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const Vector3& GetVelocity() const { return velocity_; }

private:
	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.05f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAcceleration = 20.0f;
	// 重力加速度（下方向）
	static inline const float kGravityAcceleration = 0.98f;
	static inline const float kAttenuationWall = 0.2f;
	static inline const float kAttenuationLanding = 0.0f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 0.5f;
	static inline const float kLimitRunSpeed = 0.5f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank = 0.04f;
	static inline const float kGroundSearchHeight = 0.06f;

	// マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		Vector3 move;
	};

	// モデル
	Model* model_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	// 接地状態フラグ
	bool onGround_ = true;
	LRDirection lrDirection_ = LRDirection::kRight;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	void InputMove();
	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);
	void UpdateOnGround(const CollisionMapInfo& info);
	void AnimateTurn();

	Vector3 CornerPosition(const Vector3& center, Corner corner);
};