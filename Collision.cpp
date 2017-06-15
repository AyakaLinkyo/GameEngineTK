#include "pch.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

//‡----------------------------------------------------‡
//‡*funcF‹…‚Æ‹…‚Ì“–‚½‚è”»’è
//‡*argF‹…AA‹…BiSphereŒ^j
//‡*returnF“–‚½‚Á‚Ä‚¢‚½‚çtrueA“–‚½‚Á‚Ä‚¢‚È‚©‚Á‚½‚çfalse
//‡----------------------------------------------------‡
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//‹…A‚ÆN‚Ì’†SÀ•W‚Ì·‚ğŒvZ‚·‚é
	Vector3 sub = sphereB.Center - sphereA.Center;

	//O•½•û‚Ì’è—‚ÅƒxƒNƒgƒ‹‚Ì’·‚³‚ğŒvZ‚·‚é
	//·•ªƒxƒNƒgƒ‹‚Ì’·‚³‚ÍA‚Q“_ŠÔ‚Ì‹——£
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//”¼Œa‚Ì˜a‚Ì‚Qæ
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}