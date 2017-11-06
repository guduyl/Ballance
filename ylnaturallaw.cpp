
#include "ylnaturallaw.h"





YLNaturalLaw::YLNaturalLaw(float m, float g, float u) :
	m_fMass(m),
	m_fGravitationalAcceleration(g),
	m_fFrictionFactor(u),
	m_fFriction(this->m_fFrictionFactor * this->m_fMass * this->m_fGravitationalAcceleration),
	m_fForce(0),
	m_fMaxVelocity(0),
	m_vct3Velocity0(QVector3D(0, 0, 0))
{
}



YLNaturalLaw::~YLNaturalLaw()
{
}





bool YLNaturalLaw::setMass(float m)
{
	this->m_fMass = m;
	this->m_fFriction = this->m_fFrictionFactor * this->m_fMass * this->m_fGravitationalAcceleration;
	return true;
}



bool YLNaturalLaw::setGravitationalAcceleration(float g)
{
	this->m_fGravitationalAcceleration = g;
	this->m_fFriction = this->m_fFrictionFactor * this->m_fMass * this->m_fGravitationalAcceleration;
	return true;
}



bool YLNaturalLaw::setFrictionFactor(float u)
{
	this->m_fFrictionFactor = u;
	this->m_fFriction = this->m_fFrictionFactor * this->m_fMass * this->m_fGravitationalAcceleration;
	return true;
}



bool YLNaturalLaw::setForce(float F)
{
	this->m_fForce = F;
	return true;
}



bool YLNaturalLaw::setMaxVelocity(float maxv)
{
	this->m_fMaxVelocity = maxv;
	return true;
}



bool YLNaturalLaw::setVelocity0(QVector3D v)
{
	this->m_vct3Velocity0 = v;
	return true;
}





float YLNaturalLaw::getMass() const
{
	return this->m_fMass;
}



float YLNaturalLaw::getGravitationalAcceleration() const
{
	return this->m_fGravitationalAcceleration;
}



float YLNaturalLaw::getFrictionFactor() const
{
	return this->m_fFrictionFactor;
}



float YLNaturalLaw::getForce() const
{
	return this->m_fForce;
}



float YLNaturalLaw::getMaxVelocity() const
{
	return this->m_fMaxVelocity;
}



QVector3D YLNaturalLaw::getVelocity0() const
{
	return this->m_vct3Velocity0;
}





QVector3D YLNaturalLaw::newVelocity(const QVector3D &dir, const float &deltatime)
{
//	qDebug() << dir << deltatime;

	QVector3D F = dir * this->m_fForce - this->m_vct3Velocity0.normalized() * this->m_fFriction;
	QVector3D v = this->m_vct3Velocity0 + F / this->m_fMass * deltatime;
	QVector3D maxv = v.normalized() * this->m_fMaxVelocity;
	if (v.x() > 0 && v.x() > maxv.x())
		v.setX(maxv.x());
	else if (v.x() < 0 && v.x() < maxv.x())
		v.setX(maxv.x());
	else if (v.x() > -0.1 && v.x() < 0.1)
		v.setX(0);
	if (v.y() > 0 && v.y() > maxv.y())
		v.setY(maxv.y());
	else if (v.y() < 0 && v.y() < maxv.y())
		v.setY(maxv.y());
	else if (v.y() > -0.1 && v.y() < 0.1)
		v.setY(0);
	if (v.z() > 0 && v.z() > maxv.z())
		v.setZ(maxv.z());
	else if (v.z() < 0 && v.z() < maxv.z())
		v.setZ(maxv.z());
	else if (v.z() > -0.1 && v.z() < 0.1)
		v.setZ(0);

//	qDebug() << v;
	this->m_vct3Velocity0 = v;
	return v;
}


































