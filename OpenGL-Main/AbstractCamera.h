#pragma once
#include"Premitives2D.h"
class CAbstractCamera
{
public:
	CAbstractCamera(void);
	~CAbstractCamera(void);
	void SetupProjection(const float fovy, const float aspectRatio, const float near = 0.1f, const float far = 1000.0f);
	virtual void Update() = 0;
	virtual void Rotate(const float yaw, const float pitch, const float roll);
	const glm::mat4 GetViewMatrix() const;
	const glm::mat4 GetProjectionMatrix() const;
	void SetPosition(const glm::vec3& v);
	const glm::vec3 GetPosition() const;
	void SetFOV(const float fov);
	const float GetFOV() const;
	const float GetAspectRatio() const;
	void CalcFrustumPlanes();
	bool IsPointInFrustum(const glm::vec3& point);
	bool IsSphereInFrustum(const glm::vec3& center, const float radius);
	bool IsBoxInFrustum(const glm::vec3& min, const glm::vec3& max);
	void GetFrustumPlanes(glm::vec4 planes[6]);
	glm::vec3 farPts[4];
	glm::vec3 nearPts[4];
protected:
	float yaw, pitch, roll, fov, aspect_ratio, Znear, Zfar;
	static glm::vec3 UP;
	glm::vec3 look;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 position;
	glm::mat4 V;       //view matrix
	glm::mat4 P;       //projection matrix
	CPlane planes[6];  //Frustum planes
};
class CFreeCamera : public CAbstractCamera
{
public:
	CFreeCamera(void);
	~CFreeCamera(void);
	void Update();
	void Walk(const float dt);
	void Strafe(const float dt);
	void Lift(const float dt);
	void SetTranslation(const glm::vec3& t);
	glm::vec3 GetTranslation() const;
	void SetSpeed(const float speed);
	const float GetSpeed() const;
protected:
	float speed; //move speed of camera in m/s
	glm::vec3 translation;
};