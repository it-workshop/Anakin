#include "gloveInterface.h"

#include "glove.h"

GloveInterface::GloveInterface() :
	mGlove(new Glove)
{
}

GloveInterface::~GloveInterface()
{
	if (isHardwareGloveSet()) {
		QObject::disconnect(mGlove, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}

	delete mGlove;
}

void GloveInterface::setHardwareGlove()
{
	mGlove->connectHardwareGlove("ttyACM0");

	if (isHardwareGloveSet()) {
		QObject::connect(mGlove, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}
}

bool GloveInterface::isHardwareGloveSet()
{
//	return mGlove->isPortSet();
	return true;
}

void GloveInterface::startSendingDatas()
{
	mGlove->startSendingData();
}

void GloveInterface::stopSendingDatas()
{
	mGlove->stopSendingData();
}

QList<int> GloveInterface::gloveDatas()
{
	return mGlove->data();
}
