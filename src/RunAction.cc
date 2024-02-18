#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

double RunAction::diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = clock1-clock2;
	double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
	return diffms;
}

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    // get time
    time_t beginnow = time(0);
    beginTime = asctime(localtime(&beginnow));
    begin = clock();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    // get time
    time_t endnow = time(0);
    endTime = asctime(localtime(&endnow));
    end = clock();

    // get the number of threads used
    int numberOfWorkerThreads = G4Threading::GetNumberOfRunningWorkerThreads();

    //
    G4RunManager* runManager = G4RunManager::GetRunManager();
    int totalEvents = runManager->GetNumberOfEventsToBeProcessed();
    G4int nofEvents = run->GetNumberOfEvent();

    // get user detector
    const auto detConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    // get user physics list
    const auto physicsList = static_cast<const PhysicsList*>(G4RunManager::GetRunManager()->GetUserPhysicsList());

    // get primary generator
    const auto generatorAction = static_cast<const PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    // G4String particleName = particleGun->GetParticleDefinition()->GetParticleName();
    const G4double particleEnergy = generatorAction->GetGunEnergy();
    // G4cout << particleEnergy << G4endl;


    // Print
    if(IsMaster())
    {
      G4cout << "                                                                                      " << G4endl;
      G4cout << "                                                                                      " << G4endl;
      G4cout << "                              ==> GEANT4 OUTPUT REPORT <==                            " << G4endl;
      G4cout << "  __________________________________ [ Job Title ] _________________________________  " << G4endl;
      G4cout << " |                                                                                  | " << G4endl;
      G4cout << " | Application for simulating LINAC head                                            | " << G4endl;
      G4cout << " | -------------------------------------------------------------------------------- | " << G4endl;
      G4cout << " | author: BUI Tien Hung                                                            | " << G4endl;
      G4cout << " | email : hungbt1908@gmail.com                                                     | " << G4endl;
      G4cout << " | adress: Institute for Nuclear Science and Technology (INST)                      | " << G4endl;
      G4cout << " |__________________________________________________________________________________| " << G4endl;
      G4cout << "                                                                                      " << G4endl;
      G4cout << "                         Starting = " << beginTime                                      << G4endl;
      G4cout << "                         Ending   = " << endTime                                        << G4endl;
      G4cout << "                                                                                      " << G4endl;  
      G4cout << " ------------------------------------------------------------------------------------ " << G4endl;
      G4cout << " # Number of worker threads        : " << numberOfWorkerThreads << " threads"           << G4endl;
      G4cout << " # Number of primary events        : " << nofEvents             << " events"            << G4endl;
      G4cout << " # Number of total events (scaled) : " << 1*nofEvents           << " events"            << G4endl;
      G4cout << " # Elapsed time                    : " << (double(diffclock(end, begin)/1000)) <<  " s" << G4endl;
      G4cout << "                                                                                      " << G4endl;
      G4cout << "                                                                                      " << G4endl;
    }
    else
    {}
}