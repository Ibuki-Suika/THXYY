#include "Bullet.h"
#include "ConcreteBulletType.h"
#include "HitChecker.h"
#include "../stgResources.h"

bool LinDan::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, -3.0f), 0, xPlayer, yPlayer, radius);
}

Texture* LinDan::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect LinDanRed::GetTexRect() const
{
	return Rect(32, 48, 16, 32);
}

BulletColor LinDanRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect LinDanPurple::GetTexRect() const
{
	return Rect(64, 80, 16, 32);
}

BulletColor LinDanPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect LinDanBlue::GetTexRect() const
{
	return Rect(96, 112, 16, 32);
}

BulletColor LinDanBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect LinDanTeal::GetTexRect() const
{
	return Rect(128, 144, 16, 32);
}

BulletColor LinDanTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect LinDanGreen::GetTexRect() const
{
	return Rect(160, 176, 16, 32);
}

BulletColor LinDanGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect LinDanYellow::GetTexRect() const
{
	return Rect(192, 208, 16, 32);
}

BulletColor LinDanYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect LinDanOrange::GetTexRect() const
{
	return Rect(224, 240, 16, 32);
}

BulletColor LinDanOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect LinDanGrey::GetTexRect() const
{
	return Rect(240, 256, 16, 32);
}

BulletColor LinDanGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool SmallJadeRound::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 1.0f, xPlayer, yPlayer, radius);
}

Texture* SmallJadeRound::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect SmallJadeRoundRed::GetTexRect() const
{
	return Rect(32, 48, 32, 48);
}

BulletColor SmallJadeRoundRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect SmallJadeRoundPurple::GetTexRect() const
{
	return Rect(64, 80, 32, 48);
}

BulletColor SmallJadeRoundPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect SmallJadeRoundBlue::GetTexRect() const
{
	return Rect(96, 112, 32, 48);
}

BulletColor SmallJadeRoundBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect SmallJadeRoundTeal::GetTexRect() const
{
	return Rect(128, 144, 32, 48);
}

BulletColor SmallJadeRoundTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect SmallJadeRoundGreen::GetTexRect() const
{
	return Rect(160, 176, 32, 48);
}

BulletColor SmallJadeRoundGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect SmallJadeRoundYellow::GetTexRect() const
{
	return Rect(192, 208, 32, 48);
}

BulletColor SmallJadeRoundYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect SmallJadeRoundOrange::GetTexRect() const
{
	return Rect(224, 240, 32, 48);
}

BulletColor SmallJadeRoundOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect SmallJadeRoundGrey::GetTexRect() const
{
	return Rect(240, 256, 32, 48);
}

BulletColor SmallJadeRoundGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool SmallJade::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 1.0f, xPlayer, yPlayer, radius);
}

Texture* SmallJade::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect SmallJadeRed::GetTexRect() const
{
	return Rect(32, 48, 48, 64);
}

BulletColor SmallJadeRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect SmallJadePurple::GetTexRect() const
{
	return Rect(64, 80, 48, 64);
}

BulletColor SmallJadePurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect SmallJadeBlue::GetTexRect() const
{
	return Rect(96, 112, 48, 64);
}

BulletColor SmallJadeBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect SmallJadeTeal::GetTexRect() const
{
	return Rect(128, 144, 48, 64);
}

BulletColor SmallJadeTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect SmallJadeGreen::GetTexRect() const
{
	return Rect(160, 176, 48, 64);
}

BulletColor SmallJadeGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect SmallJadeYellow::GetTexRect() const
{
	return Rect(192, 208, 48, 64);
}

BulletColor SmallJadeYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect SmallJadeOrange::GetTexRect() const
{
	return Rect(224, 240, 48, 64);
}

BulletColor SmallJadeOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect SmallJadeGrey::GetTexRect() const
{
	return Rect(240, 256, 48, 64);
}

BulletColor SmallJadeGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Chain::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 3.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* Chain::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect ChainRed::GetTexRect() const
{
	return Rect(32, 48, 80, 96);
}

BulletColor ChainRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect ChainPurple::GetTexRect() const
{
	return Rect(64, 80, 80, 96);
}

BulletColor ChainPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect ChainBlue::GetTexRect() const
{
	return Rect(96, 112, 80, 96);
}

BulletColor ChainBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect ChainTeal::GetTexRect() const
{
	return Rect(128, 144, 80, 96);
}

BulletColor ChainTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect ChainGreen::GetTexRect() const
{
	return Rect(160, 176, 80, 96);
}

BulletColor ChainGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect ChainYellow::GetTexRect() const
{
	return Rect(192, 208, 80, 96);
}

BulletColor ChainYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect ChainOrange::GetTexRect() const
{
	return Rect(224, 240, 80, 96);
}

BulletColor ChainOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect ChainGrey::GetTexRect() const
{
	return Rect(240, 256, 80, 96);
}

BulletColor ChainGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Rice::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* Rice::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect RiceRed::GetTexRect() const
{
	return Rect(32, 48, 65, 79);
}

BulletColor RiceRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect RicePurple::GetTexRect() const
{
	return Rect(64, 80, 65, 79);
}

BulletColor RicePurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect RiceBlue::GetTexRect() const
{
	return Rect(96, 112, 65, 79);
}

BulletColor RiceBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect RiceTeal::GetTexRect() const
{
	return Rect(128, 144, 65, 79);
}

BulletColor RiceTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect RiceGreen::GetTexRect() const
{
	return Rect(160, 176, 65, 79);
}

BulletColor RiceGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect RiceYellow::GetTexRect() const
{
	return Rect(192, 208, 65, 79);
}

BulletColor RiceYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect RiceOrange::GetTexRect() const
{
	return Rect(224, 240, 65, 79);
}

BulletColor RiceOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect RiceGrey::GetTexRect() const
{
	return Rect(240, 256, 65, 79);
}

BulletColor RiceGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool ChongDan::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 1.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* ChongDan::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect ChongDanRed::GetTexRect() const
{
	return Rect(32, 48, 128, 144);
}

BulletColor ChongDanRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect ChongDanPurple::GetTexRect() const
{
	return Rect(64, 80, 128, 144);
}

BulletColor ChongDanPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect ChongDanBlue::GetTexRect() const
{
	return Rect(96, 112, 128, 144);
}

BulletColor ChongDanBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect ChongDanTeal::GetTexRect() const
{
	return Rect(128, 144, 128, 144);
}

BulletColor ChongDanTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect ChongDanGreen::GetTexRect() const
{
	return Rect(160, 176, 128, 144);
}

BulletColor ChongDanGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect ChongDanYellow::GetTexRect() const
{
	return Rect(192, 208, 128, 144);
}

BulletColor ChongDanYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect ChongDanOrange::GetTexRect() const
{
	return Rect(224, 240, 128, 144);
}

BulletColor ChongDanOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect ChongDanGrey::GetTexRect() const
{
	return Rect(240, 256, 128, 144);
}

BulletColor ChongDanGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool ZhaDan::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitSquare(this->bullet, Vector2f(0.0f, 0.0f), Vector2f(0.0f, 0.0f), xPlayer, yPlayer, radius);
}

Texture* ZhaDan::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect ZhaDanRed::GetTexRect() const
{
	return Rect(32, 48, 112, 128);
}

BulletColor ZhaDanRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect ZhaDanPurple::GetTexRect() const
{
	return Rect(64, 80, 112, 128);
}

BulletColor ZhaDanPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect ZhaDanBlue::GetTexRect() const
{
	return Rect(96, 112, 112, 128);
}

BulletColor ZhaDanBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect ZhaDanTeal::GetTexRect() const
{
	return Rect(128, 144, 128, 144);
}

BulletColor ZhaDanTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect ZhaDanGreen::GetTexRect() const
{
	return Rect(160, 176, 112, 128);
}

BulletColor ZhaDanGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect ZhaDanYellow::GetTexRect() const
{
	return Rect(192, 208, 112, 128);
}

BulletColor ZhaDanYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect ZhaDanOrange::GetTexRect() const
{
	return Rect(224, 240, 112, 128);
}

BulletColor ZhaDanOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect ZhaDanGrey::GetTexRect() const
{
	return Rect(240, 256, 112, 128);
}

BulletColor ZhaDanGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Bacilli::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* Bacilli::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect BacilliRed::GetTexRect() const
{
	return Rect(16, 32, 144, 160);
}

BulletColor BacilliRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect BacilliPurple::GetTexRect() const
{
	return Rect(48, 64, 144, 160);
}

BulletColor BacilliPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect BacilliBlue::GetTexRect() const
{
	return Rect(80, 96, 144, 160);
}

BulletColor BacilliBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect BacilliTeal::GetTexRect() const
{
	return Rect(112, 128, 144, 160);
}

BulletColor BacilliTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect BacilliGreen::GetTexRect() const
{
	return Rect(144, 160, 144, 160);
}

BulletColor BacilliGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect BacilliYellow::GetTexRect() const
{
	return Rect(176, 192, 144, 160);
}

BulletColor BacilliYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect BacilliOrange::GetTexRect() const
{
	return Rect(208, 224, 144, 160);
}

BulletColor BacilliOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect BacilliGrey::GetTexRect() const
{
	return Rect(240, 256, 144, 160);
}

BulletColor BacilliGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool SmallStar::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 1.0f, xPlayer, yPlayer, radius);
}

Texture* SmallStar::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect SmallStarRed::GetTexRect() const
{
	return Rect(32, 48, 160, 176);
}

BulletColor SmallStarRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect SmallStarPurple::GetTexRect() const
{
	return Rect(64, 80, 160, 176);
}

BulletColor SmallStarPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect SmallStarBlue::GetTexRect() const
{
	return Rect(96, 112, 160, 176);
}

BulletColor SmallStarBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect SmallStarTeal::GetTexRect() const
{
	return Rect(128, 144, 160, 176);
}

BulletColor SmallStarTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect SmallStarGreen::GetTexRect() const
{
	return Rect(160, 176, 160, 176);
}

BulletColor SmallStarGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect SmallStarYellow::GetTexRect() const
{
	return Rect(192, 208, 160, 176);
}

BulletColor SmallStarYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect SmallStarOrange::GetTexRect() const
{
	return Rect(224, 240, 160, 176);
}

BulletColor SmallStarOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect SmallStarGrey::GetTexRect() const
{
	return Rect(240, 256, 160, 176);
}

BulletColor SmallStarGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool PointBullet::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* PointBullet::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect PointBulletRed::GetTexRect() const
{
	return Rect(8, 16, 240, 248);
}

BulletColor PointBulletRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect PointBulletPurple::GetTexRect() const
{
	return Rect(24, 32, 240, 248);
}

BulletColor PointBulletPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect PointBulletBlue::GetTexRect() const
{
	return Rect(40, 48, 240, 248);
}

BulletColor PointBulletBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect PointBulletTeal::GetTexRect() const
{
	return Rect(56, 64, 240, 248);
}

BulletColor PointBulletTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect PointBulletGreen::GetTexRect() const
{
	return Rect(8, 16, 240, 256);
}

BulletColor PointBulletGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect PointBulletYellow::GetTexRect() const
{
	return Rect(32, 40, 248, 256);
}

BulletColor PointBulletYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect PointBulletOrange::GetTexRect() const
{
	return Rect(48, 56, 248, 256);
}

BulletColor PointBulletOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect PointBulletGrey::GetTexRect() const
{
	return Rect(56, 64, 248, 256);
}

BulletColor PointBulletGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Needle::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* Needle::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect NeedleRed::GetTexRect() const
{
	return Rect(32, 48, 96, 112);
}

BulletColor NeedleRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect NeedlePurple::GetTexRect() const
{
	return Rect(64, 80, 96, 112);
}

BulletColor NeedlePurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect NeedleBlue::GetTexRect() const
{
	return Rect(96, 112, 96, 112);
}

BulletColor NeedleBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect NeedleTeal::GetTexRect() const
{
	return Rect(128, 144, 96, 112);
}

BulletColor NeedleTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect NeedleGreen::GetTexRect() const
{
	return Rect(160, 176, 96, 112);
}

BulletColor NeedleGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect NeedleYellow::GetTexRect() const
{
	return Rect(192, 208, 96, 112);
}

BulletColor NeedleYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect NeedleOrange::GetTexRect() const
{
	return Rect(224, 240, 96, 112);
}

BulletColor NeedleOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect NeedleGrey::GetTexRect() const
{
	return Rect(240, 256, 96, 112);
}

BulletColor NeedleGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Bacteria::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* Bacteria::GetTexture() const
{
	return STGResources::GetInstance()->texBullet01;
}

Rect BacteriaRed::GetTexRect() const
{
	return Rect(8, 16, 192, 200);
}

BulletColor BacteriaRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect BacteriaPurple::GetTexRect() const
{
	return Rect(24, 32, 192, 200);
}

BulletColor BacteriaPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect BacteriaBlue::GetTexRect() const
{
	return Rect(40, 48, 192, 200);
}

BulletColor BacteriaBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect BacteriaTeal::GetTexRect() const
{
	return Rect(56, 64, 192, 200);
}

BulletColor BacteriaTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect BacteriaGreen::GetTexRect() const
{
	return Rect(8, 16, 200, 208);
}

BulletColor BacteriaGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect BacteriaYellow::GetTexRect() const
{
	return Rect(32, 40, 200, 208);
}

BulletColor BacteriaYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect BacteriaOrange::GetTexRect() const
{
	return Rect(48, 56, 200, 208);
}

BulletColor BacteriaOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect BacteriaGrey::GetTexRect() const
{
	return Rect(56, 64, 200, 208);
}

BulletColor BacteriaGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool BigStar::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 3.0f, xPlayer, yPlayer, radius);
}

Texture* BigStar::GetTexture() const
{
	return STGResources::GetInstance()->texBullet02;
}

Rect BigStarRed::GetTexRect() const
{
	return Rect(0, 32, 0, 32);
}

BulletColor BigStarRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect BigStarPurple::GetTexRect() const
{
	return Rect(32, 64, 0, 32);
}

BulletColor BigStarPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect BigStarBlue::GetTexRect() const
{
	return Rect(64, 96, 0, 32);
}

BulletColor BigStarBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect BigStarTeal::GetTexRect() const
{
	return Rect(96, 128, 0, 32);
}

BulletColor BigStarTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect BigStarGreen::GetTexRect() const
{
	return Rect(128, 160, 0, 32);
}

BulletColor BigStarGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect BigStarYellow::GetTexRect() const
{
	return Rect(160, 192, 0, 32);
}

BulletColor BigStarYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect BigStarOrange::GetTexRect() const
{
	return Rect(192, 224, 0, 32);
}

BulletColor BigStarOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect BigStarGrey::GetTexRect() const
{
	return Rect(224, 256, 0, 32);
}

BulletColor BigStarGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool MidJade::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 5.0f, xPlayer, yPlayer, radius);
}

Texture* MidJade::GetTexture() const
{
	return STGResources::GetInstance()->texBullet02;
}

Rect MidJadeRed::GetTexRect() const
{
	return Rect(0, 32, 32, 64);
}

BulletColor MidJadeRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect MidJadePurple::GetTexRect() const
{
	return Rect(32, 64, 32, 64);
}

BulletColor MidJadePurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect MidJadeBlue::GetTexRect() const
{
	return Rect(64, 96, 32, 64);
}

BulletColor MidJadeBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect MidJadeTeal::GetTexRect() const
{
	return Rect(96, 128, 32, 64);
}

BulletColor MidJadeTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect MidJadeGreen::GetTexRect() const
{
	return Rect(128, 160, 32, 64);
}

BulletColor MidJadeGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect MidJadeYellow::GetTexRect() const
{
	return Rect(160, 192, 32, 64);
}

BulletColor MidJadeYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect MidJadeOrange::GetTexRect() const
{
	return Rect(192, 224, 32, 64);
}

BulletColor MidJadeOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect MidJadeGrey::GetTexRect() const
{
	return Rect(224, 256, 32, 64);
}

BulletColor MidJadeGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool ButterflyBullet::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.5f, 0.5f), 1.0f, xPlayer, yPlayer, radius);
}

Texture* ButterflyBullet::GetTexture() const
{
	return STGResources::GetInstance()->texBullet02;
}

Rect ButterflyBulletRed::GetTexRect() const
{
	return Rect(0, 32, 64, 96);
}

BulletColor ButterflyBulletRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect ButterflyBulletPurple::GetTexRect() const
{
	return Rect(32, 64, 64, 96);
}

BulletColor ButterflyBulletPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect ButterflyBulletBlue::GetTexRect() const
{
	return Rect(64, 96, 64, 96);
}

BulletColor ButterflyBulletBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect ButterflyBulletTeal::GetTexRect() const
{
	return Rect(96, 128, 64, 96);
}

BulletColor ButterflyBulletTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect ButterflyBulletGreen::GetTexRect() const
{
	return Rect(128, 160, 64, 96);
}

BulletColor ButterflyBulletGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect ButterflyBulletYellow::GetTexRect() const
{
	return Rect(160, 192, 64, 96);
}

BulletColor ButterflyBulletYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect ButterflyBulletOrange::GetTexRect() const
{
	return Rect(192, 224, 64, 96);
}

BulletColor ButterflyBulletOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect ButterflyBulletGrey::GetTexRect() const
{
	return Rect(224, 256, 64, 96);
}

BulletColor ButterflyBulletGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Knife::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitSquare(this->bullet, Vector2f(0.0f, 2.0f), Vector2f(1.0f, 4.0f), xPlayer, yPlayer, radius);
}

Texture* Knife::GetTexture() const
{
	return STGResources::GetInstance()->texBullet02;
}

Rect KnifeRed::GetTexRect() const
{
	return Rect(0, 32, 96, 128);
}

BulletColor KnifeRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect KnifePurple::GetTexRect() const
{
	return Rect(32, 64, 96, 128);
}

BulletColor KnifePurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect KnifeBlue::GetTexRect() const
{
	return Rect(64, 96, 96, 128);
}

BulletColor KnifeBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect KnifeTeal::GetTexRect() const
{
	return Rect(96, 128, 96, 128);
}

BulletColor KnifeTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect KnifeGreen::GetTexRect() const
{
	return Rect(128, 160, 96, 128);
}

BulletColor KnifeGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect KnifeYellow::GetTexRect() const
{
	return Rect(160, 192, 96, 128);
}

BulletColor KnifeYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect KnifeOrange::GetTexRect() const
{
	return Rect(192, 224, 96, 128);
}

BulletColor KnifeOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect KnifeGrey::GetTexRect() const
{
	return Rect(224, 256, 96, 128);
}

BulletColor KnifeGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool EllipseBullet::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 2.0f, xPlayer, yPlayer, radius);
}

Texture* EllipseBullet::GetTexture() const
{
	return STGResources::GetInstance()->texBullet02;
}

Rect EllipseBulletRed::GetTexRect() const
{
	return Rect(0, 32, 128, 160);
}

BulletColor EllipseBulletRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect EllipseBulletPurple::GetTexRect() const
{
	return Rect(32, 64, 128, 160);
}

BulletColor EllipseBulletPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect EllipseBulletBlue::GetTexRect() const
{
	return Rect(64, 96, 128, 160);
}

BulletColor EllipseBulletBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect EllipseBulletTeal::GetTexRect() const
{
	return Rect(96, 128, 128, 160);
}

BulletColor EllipseBulletTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect EllipseBulletGreen::GetTexRect() const
{
	return Rect(128, 160, 128, 160);
}

BulletColor EllipseBulletGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect EllipseBulletYellow::GetTexRect() const
{
	return Rect(160, 192, 128, 160);
}

BulletColor EllipseBulletYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect EllipseBulletOrange::GetTexRect() const
{
	return Rect(192, 224, 128, 160);
}

BulletColor EllipseBulletOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect EllipseBulletGrey::GetTexRect() const
{
	return Rect(224, 256, 128, 160);
}

BulletColor EllipseBulletGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool DiDan::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 1.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* DiDan::GetTexture() const
{
	return STGResources::GetInstance()->texBullet03;
}

Rect DiDanRed::GetTexRect() const
{
	return Rect(32, 48, 192, 208);
}

BulletColor DiDanRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect DiDanPurple::GetTexRect() const
{
	return Rect(64, 80, 192, 208);
}

BulletColor DiDanPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect DiDanBlue::GetTexRect() const
{
	return Rect(96, 112, 192, 208);
}

BulletColor DiDanBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect DiDanTeal::GetTexRect() const
{
	return Rect(128, 144, 192, 208);
}

BulletColor DiDanTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect DiDanGreen::GetTexRect() const
{
	return Rect(160, 176, 192, 208);
}

BulletColor DiDanGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect DiDanYellow::GetTexRect() const
{
	return Rect(192, 208, 192, 208);
}

BulletColor DiDanYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect DiDanOrange::GetTexRect() const
{
	return Rect(224, 240, 192, 208);
}

BulletColor DiDanOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect DiDanGrey::GetTexRect() const
{
	return Rect(240, 256, 192, 208);
}

BulletColor DiDanGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Heart::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 5.0f, xPlayer, yPlayer, radius);
}

Texture* Heart::GetTexture() const
{
	return STGResources::GetInstance()->texBullet03;
}

Rect HeartRed::GetTexRect() const
{
	return Rect(0, 32, 0, 32);
}

BulletColor HeartRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect HeartPurple::GetTexRect() const
{
	return Rect(32, 64, 0, 32);
}

BulletColor HeartPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect HeartBlue::GetTexRect() const
{
	return Rect(64, 96, 0, 32);
}

BulletColor HeartBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect HeartTeal::GetTexRect() const
{
	return Rect(96, 128, 0, 32);
}

BulletColor HeartTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect HeartGreen::GetTexRect() const
{
	return Rect(128, 160, 0, 32);
}

BulletColor HeartGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect HeartYellow::GetTexRect() const
{
	return Rect(160, 192, 0, 32);
}

BulletColor HeartYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect HeartOrange::GetTexRect() const
{
	return Rect(192, 224, 0, 32);
}

BulletColor HeartOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect HeartGrey::GetTexRect() const
{
	return Rect(224, 256, 0, 32);
}

BulletColor HeartGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool Arrow::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 8.0f), 0.0f, xPlayer, yPlayer, radius);
}

Texture* Arrow::GetTexture() const
{
	return STGResources::GetInstance()->texBullet03;
}

Rect ArrowRed::GetTexRect() const
{
	return Rect(0, 32, 32, 64);
}

BulletColor ArrowRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect ArrowPurple::GetTexRect() const
{
	return Rect(32, 64, 32, 64);
}

BulletColor ArrowPurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect ArrowBlue::GetTexRect() const
{
	return Rect(64, 96, 32, 64);
}

BulletColor ArrowBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect ArrowTeal::GetTexRect() const
{
	return Rect(96, 128, 32, 64);
}

BulletColor ArrowTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect ArrowGreen::GetTexRect() const
{
	return Rect(128, 160, 32, 64);
}

BulletColor ArrowGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect ArrowYellow::GetTexRect() const
{
	return Rect(160, 192, 32, 64);
}

BulletColor ArrowYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect ArrowOrange::GetTexRect() const
{
	return Rect(192, 224, 32, 64);
}

BulletColor ArrowOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect ArrowGrey::GetTexRect() const
{
	return Rect(224, 256, 32, 64);
}

BulletColor ArrowGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}

////////////////////////////////////////////////////////////////////

bool BigJade::Hit(float xPlayer, float yPlayer, float radius) const
{
	return HitChecker::HitRound(this->bullet, Vector2f(0.0f, 0.0f), 13.0f, xPlayer, yPlayer, radius);
}

Texture* BigJade::GetTexture() const
{
	return STGResources::GetInstance()->texBullet04;
}

Rect BigJadeRed::GetTexRect() const
{
	return Rect(0, 64, 0, 64);
}

BulletColor BigJadeRed::GetBulletColor() const
{
	return BulletColor::BULLET_RED;
}

Rect BigJadePurple::GetTexRect() const
{
	return Rect(64, 128, 0, 64);
}

BulletColor BigJadePurple::GetBulletColor() const
{
	return BulletColor::BULLET_PURPLE;
}

Rect BigJadeBlue::GetTexRect() const
{
	return Rect(128, 192, 0, 64);
}

BulletColor BigJadeBlue::GetBulletColor() const
{
	return BulletColor::BULLET_BLUE;
}

Rect BigJadeTeal::GetTexRect() const
{
	return Rect(192, 256, 0, 64);
}

BulletColor BigJadeTeal::GetBulletColor() const
{
	return BulletColor::BULLET_TEAL;
}

Rect BigJadeGreen::GetTexRect() const
{
	return Rect(0, 64, 64, 128);
}

BulletColor BigJadeGreen::GetBulletColor() const
{
	return BulletColor::BULLET_GREEN;
}

Rect BigJadeYellow::GetTexRect() const
{
	return Rect(64, 128, 64, 128);
}

BulletColor BigJadeYellow::GetBulletColor() const
{
	return BulletColor::BULLET_YELLOW;
}

Rect BigJadeOrange::GetTexRect() const
{
	return Rect(128, 192, 64, 128);
}

BulletColor BigJadeOrange::GetBulletColor() const
{
	return BulletColor::BULLET_ORANGE;
}

Rect BigJadeGrey::GetTexRect() const
{
	return Rect(192, 256, 64, 128);
}

BulletColor BigJadeGrey::GetBulletColor() const
{
	return BulletColor::BULLET_GREY;
}