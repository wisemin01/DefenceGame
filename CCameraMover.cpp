#include "DXUT.h"
#include "CCameraMover.h"


CCameraMover::CCameraMover(float fScreenX, float fScreenY, float fSpeed)
	:m_fScreenX(fScreenX), m_fScreenY(fScreenY), m_fSpeed(fSpeed)
{
}

CCameraMover::~CCameraMover()
{
}

void CCameraMover::Init()
{
}

void CCameraMover::Update()
{
	Vector3 velocity(0, 0, 0);
	Vector3 mouse = INPUT.GetScreenMouse();
	Vector3 camera = CAMERA.GetPosition();

	if (mouse.x <= 50)
		velocity.x -= m_fSpeed * DXUTGetElapsedTime();
	if (mouse.x >= WINSIZEX - 50)
		velocity.x += m_fSpeed * DXUTGetElapsedTime();
	if (mouse.y <= 50)
		velocity.y -= m_fSpeed * DXUTGetElapsedTime();
	if (mouse.y >= WINSIZEY - 50)
		velocity.y += m_fSpeed * DXUTGetElapsedTime();

	if (camera.x + velocity.x + WINSIZEX / 2 >= m_fScreenX)
		velocity.x = velocity.x > 0 ? 0 : velocity.x;
	if (camera.x + velocity.x - WINSIZEX / 2 <= 0)
		velocity.x = velocity.x < 0 ? 0 : velocity.x;
	if (camera.y + velocity.y + WINSIZEY / 2 >= m_fScreenY)
		velocity.y = velocity.y > 0 ? 0 : velocity.y;
	if (camera.y + velocity.y - WINSIZEY / 2 <= 0)
		velocity.y = velocity.y < 0 ? 0 : velocity.y;
	

	CAMERA.MovePosition(velocity);

}

void CCameraMover::Render()
{
}

void CCameraMover::Destroy()
{
}
