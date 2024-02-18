#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction);
}


void ActionInitialization::Build() const
{
	PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
	SetUserAction(generator);

	SetUserAction(new RunAction);
}  

