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
	static Texture explosionTex;
	static Texture gameLogoTex;

	static Texture creditsButtonTex;
	static Texture exitButtonTex;
	static Texture helpButtonTex;
	static Texture playButtonTex;

	static Texture enemyBulletTex;
	static Texture enemyMissileTex;
	static Texture enemyBodyTex;

	static Texture playerBulletTex;
	static Texture playerMissileTex;
	static Texture playerBodyTex;

	static Texture seaTex;
	static Texture seaElem1;
	static Texture seaElem2;
};
#endif
