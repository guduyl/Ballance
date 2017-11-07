
#include "ylnaturallaw.h"





YLNaturalLaw::YLNaturalLaw(float m, float g, float u) :
	m_fMass(m),
	m_fGravitationalAcceleration(g),
	m_fGravity(m_fMass * m_fGravitationalAcceleration),
	m_fFrictionFactor(u),
	m_fFriction(m_fFrictionFactor * m_fMass * m_fGravitationalAcceleration),
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
	m_fMass = m;
	m_fGravity = m_fMass * m_fGravitationalAcceleration;
	m_fFriction = m_fFrictionFactor * m_fMass * m_fGravitationalAcceleration;
	return true;
}



bool YLNaturalLaw::setGravitationalAcceleration(float g)
{
	m_fGravitationalAcceleration = g;
	m_fGravity = m_fMass * m_fGravitationalAcceleration;
	m_fFriction = m_fFrictionFactor * m_fMass * m_fGravitationalAcceleration;
	return true;
}



bool YLNaturalLaw::setFrictionFactor(float u)
{
	m_fFrictionFactor = u;
	m_fFriction = m_fFrictionFactor * m_fMass * m_fGravitationalAcceleration;
	return true;
}



bool YLNaturalLaw::setForce(float F)
{
	m_fForce = F;
	return true;
}



bool YLNaturalLaw::setMaxVelocity(float maxv)
{
	m_fMaxVelocity = maxv;
	return true;
}



bool YLNaturalLaw::setVelocity0(QVector3D v)
{
	m_vct3Velocity0 = v;
	return true;
}





float YLNaturalLaw::getMass() const
{
	return m_fMass;
}



float YLNaturalLaw::getGravitationalAcceleration() const
{
	return m_fGravitationalAcceleration;
}



float YLNaturalLaw::getGravity() const
{
	return m_fGravity;
}



float YLNaturalLaw::getFrictionFactor() const
{
	return m_fFrictionFactor;
}



float YLNaturalLaw::getFriction() const
{
	return m_fFriction;
}



float YLNaturalLaw::getForce() const
{
	return m_fForce;
}



float YLNaturalLaw::getMaxVelocity() const
{
	return m_fMaxVelocity;
}



QVector3D YLNaturalLaw::getVelocity0() const
{
	return m_vct3Velocity0;
}





QVector3D YLNaturalLaw::Displacement(const QVector3D &dir, const float &deltatime)
{
//	qDebug() << dir << deltatime;

	QVector3D dirv0 = m_vct3Velocity0.normalized();
//	QVector3D F = dir * m_fForce - m_vct3Velocity0.normalized() * m_fFriction;
	QVector3D F = QVector3D(dir.x() * m_fForce - dirv0.x() * m_fFriction,
							dir.y() * m_fForce - dirv0.y() * m_fFriction,
							dir.z() * m_fGravity);
	QVector3D v = m_vct3Velocity0 + F / m_fMass * deltatime;
	QVector3D maxv = v.normalized() * m_fMaxVelocity;
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

//	qDebug() << v;
	QVector3D displ = (m_vct3Velocity0 + v) * deltatime;
	m_vct3Velocity0 = v;
	return displ;
}


































