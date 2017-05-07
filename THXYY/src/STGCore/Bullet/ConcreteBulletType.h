#pragma once

#include "BulletType.h"

class LinDan : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class LinDanRed : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanPurple : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanBlue : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanTeal : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanGreen : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanYellow : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanOrange : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class LinDanGrey : public LinDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

/////////////////////////////////////////////////////////////

class SmallJadeRound : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class SmallJadeRoundRed : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundPurple : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundBlue : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundTeal : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundGreen : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundYellow : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundOrange : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeRoundGrey : public SmallJadeRound
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class SmallJade : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class SmallJadeRed : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadePurple : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeBlue : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeTeal : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeGreen : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeYellow : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeOrange : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallJadeGrey : public SmallJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Chain : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class ChainRed : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainPurple : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainBlue : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainTeal : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainGreen : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainYellow : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainOrange : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChainGrey : public Chain
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Rice : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class RiceRed : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RicePurple : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RiceBlue : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RiceTeal : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RiceGreen : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RiceYellow : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RiceOrange : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class RiceGrey : public Rice
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class ChongDan : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class ChongDanRed : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanPurple : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanBlue : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanTeal : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanGreen : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanYellow : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanOrange : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ChongDanGrey : public ChongDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class ZhaDan : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class ZhaDanRed : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanPurple : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanBlue : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanTeal : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanGreen : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanYellow : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanOrange : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ZhaDanGrey : public ZhaDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Bacilli : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class BacilliRed : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliPurple : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliBlue : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliTeal : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliGreen : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliYellow : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliOrange : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacilliGrey : public Bacilli
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class SmallStar : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class SmallStarRed : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarPurple : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarBlue : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarTeal : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarGreen : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarYellow : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarOrange : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class SmallStarGrey : public SmallStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class PointBullet : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class PointBulletRed : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletPurple : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletBlue : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletTeal : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletGreen : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletYellow : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletOrange : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class PointBulletGrey : public PointBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Needle : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class NeedleRed : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedlePurple : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedleBlue : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedleTeal : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedleGreen : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedleYellow : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedleOrange : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class NeedleGrey : public Needle
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Bacteria : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class BacteriaRed : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaPurple : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaBlue : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaTeal : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaGreen : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaYellow : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaOrange : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BacteriaGrey : public Bacteria
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class BigStar : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class BigStarRed : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarPurple : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarBlue : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarTeal : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarGreen : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarYellow : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarOrange : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigStarGrey : public BigStar
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class MidJade : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class MidJadeRed : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadePurple : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadeBlue : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadeTeal : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadeGreen : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadeYellow : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadeOrange : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class MidJadeGrey : public MidJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class ButterflyBullet : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class ButterflyBulletRed : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletPurple : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletBlue : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletTeal : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletGreen : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletYellow : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletOrange : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ButterflyBulletGrey : public ButterflyBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Knife : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class KnifeRed : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifePurple : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifeBlue : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifeTeal : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifeGreen : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifeYellow : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifeOrange : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class KnifeGrey : public Knife
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class EllipseBullet : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class EllipseBulletRed : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletPurple : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletBlue : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletTeal : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletGreen : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletYellow : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletOrange : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class EllipseBulletGrey : public EllipseBullet
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class DiDan : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class DiDanRed : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanPurple : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanBlue : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanTeal : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanGreen : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanYellow : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanOrange : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class DiDanGrey : public DiDan
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Heart : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class HeartRed : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartPurple : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartBlue : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartTeal : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartGreen : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartYellow : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartOrange : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class HeartGrey : public Heart
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class Arrow : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class ArrowRed : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowPurple : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowBlue : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowTeal : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowGreen : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowYellow : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowOrange : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class ArrowGrey : public Arrow
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

//////////////////////////////////////////////////////

class BigJade : public BulletType
{
public:
	virtual bool Hit(float xPlayer, float yPlayer, float radius) const override;
	virtual Texture* GetTexture() const override;
};

class BigJadeRed : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadePurple : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadeBlue : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadeTeal : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadeGreen : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadeYellow : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadeOrange : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};

class BigJadeGrey : public BigJade
{
public:
	virtual Rect GetTexRect() const override;
	virtual BulletColor GetBulletColor() const override;
};