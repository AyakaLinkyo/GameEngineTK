#include "pch.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

//��----------------------------------------------------��
//��*func�F���Ƌ��̓����蔻��
//��*arg�F��A�A��B�iSphere�^�j
//��*return�F�������Ă�����true�A�������Ă��Ȃ�������false
//��----------------------------------------------------��
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//��A��N�̒��S���W�̍����v�Z����
	Vector3 sub = sphereB.Center - sphereA.Center;

	//�O�����̒藝�Ńx�N�g���̒������v�Z����
	//�����x�N�g���̒����́A�Q�_�Ԃ̋���
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//���a�̘a�̂Q��
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//���������a�̘a���傫����Γ������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}