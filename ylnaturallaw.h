
#ifndef YLNATURALLAW_H
#define YLNATURALLAW_H

#include <QVector3D>

#include <QDebug>





class YLNaturalLaw
{
public:
	YLNaturalLaw(float m, float g, float u);
	~YLNaturalLaw();

	bool setMass(float m);
	bool setGravitationalAcceleration(float g);
	bool setFrictionFactor(float u);
	bool setForce(float F);
	bool setMaxVelocity(float maxv);
	bool setVelocity0(QVector3D v);

	float getMass() const;
	float getGravitationalAcceleration() const;
	float getGravity() const;
	float getFrictionFactor() const;
	float getFriction() const;
	float getForce() const;
	float getMaxVelocity() const;
	QVector3D getVelocity0() const;

	QVector3D Displacement(const QVector3D &dir, const float &deltatime);

protected:

private:
	float m_fMass;																//质量
	float m_fGravitationalAcceleration;											//重力加速度
	float m_fGravity;															//重力（只能get）
	float m_fFrictionFactor;													//摩擦因数
	float m_fFriction;															//摩擦力（只能get）
	float m_fForce;																//合外力
	float m_fMaxVelocity;														//最大速度
	QVector3D m_vct3Velocity0;													//初速度

};


































#endif // YLNATURALLAW_H





