#ifndef GetTexture_air321
#define GetTexture_air321

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class GetRes
{
public:
	GetRes();
	static Font boldFont;
	static Font gameFont;
	static Font techFont;
	static Texture explosionTex;
	static Texture gameLogoTex;

	static Texture creditsButtonTex;
	static Texture exitButtonTex;
	static Texture helpButtonTex;
	static Texture playButtonTex;

	static Texture enemyBulletTex;
	static Texture enemyMissileTex;
	static Texture enemyBodyTex1;
	static Texture enemyBodyTex2;
	static Texture enemyBodyTex3;
	static Texture enemyBodyTex4;
	static Texture enemyBodyTex5;
	static Texture enemyBodyTex6;
	static Texture enemyBodyTex7;

	static Texture playerBulletTex;
	static Texture playerMissileTex;
	static Texture playerBodyTex;

	static Texture seaTex;
	static Texture seaElem1;
	static Texture seaElem2;

	static Texture CompleteBody;
	static Texture CompleteStar;
	static Texture CompleteText;
	static Texture CompleteButton;
};
#endif
