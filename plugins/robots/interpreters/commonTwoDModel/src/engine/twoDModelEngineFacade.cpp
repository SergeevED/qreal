#include "commonTwoDModel/engine/twoDModelEngineFacade.h"

#include "src/engine/d2RobotModel.h"

using namespace twoDModel::engine;

TwoDModelEngineFacade::TwoDModelEngineFacade(interpreterBase::robotModel::RobotModelInterface &robotModel)
	: mTwoDModelActionInfo(
			new QAction(QIcon(":/icons/2d-model.svg"), QObject::tr("2d model"), nullptr)
			, "interpreters"
			, "tools")
	, mTwoDModel(new D2RobotModel(robotModel))
{
	/// @todo: why it can't be done in constructor?
	mTwoDModel->createModelWidget();

	connect(mTwoDModelActionInfo.action(), &QAction::triggered
			, mTwoDModel.data(), &twoDModel::D2RobotModel::showModelWidget);

	connect(mTwoDModel.data(), &D2RobotModel::runButtonPressed, this, &TwoDModelEngineFacade::runButtonPressed);
	connect(mTwoDModel.data(), &D2RobotModel::stopButtonPressed, this, &TwoDModelEngineFacade::stopButtonPressed);
}

TwoDModelEngineFacade::~TwoDModelEngineFacade()
{
	delete mTwoDModelActionInfo.action();
}

qReal::ActionInfo &TwoDModelEngineFacade::showTwoDModelWidgetActionInfo()
{
	return mTwoDModelActionInfo;
}

interpreterBase::SensorsConfigurationProvider &TwoDModelEngineFacade::sensorsConfigurationProvider()
{
	return *mTwoDModel;
}

TwoDModelEngineInterface &TwoDModelEngineFacade::engine()
{
	return *mTwoDModel;
}

void TwoDModelEngineFacade::onStartInterpretation()
{
	mTwoDModel->startInterpretation();
}

void TwoDModelEngineFacade::onStopInterpretation()
{
	mTwoDModel->stopRobot();
}