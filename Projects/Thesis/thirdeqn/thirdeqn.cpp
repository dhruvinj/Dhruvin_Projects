
#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/transport.h"
#include "cantera/kinetics/Kinetics.h"
#include "cantera/kinetics/GasKinetics.h"
#include "cantera/kinetics/Reaction.h"
#include "cantera/base/utilities.h"
#include "cantera/kinetics/RxnRates.h"
#include "cantera/kinetics/Reaction.h"


int main(int argc, char* argv[])
{


Cantera::IdealGasMix gas("inputfileedi.xml","gri30_mix");

doublereal temp = 2000.0; // K
doublereal pressure = 1.0*Cantera::OneAtm; //atm
doublereal uin=0.3; //m/sec

gas.setState_TPX(temp, pressure, "O3:0.53, O2:0.47");
int nsp = gas.nSpecies();


Cantera::ReactionData* r2 = new Cantera::ReactionData;
	r2->number(2);




return 0;
}

/*


std::cout << gas.reactionString(2) << "\n";







Cantera::ReactionData* rdata = new Cantera::ReactionData;
rdata->number = 2;
Cantera::FreeFlame flow(&gas);
flow.setKinetics(gas);

std::vector<double> net_production_rates(3,0.0);
gas.getNetProductionRates(&net_production_rates[0]);

for( unsigned int i = 0; i < 3; i++ )
	std::cout << "wdot[" << i << "] = " << net_production_rates[i] << std::endl;

std::tr1::shared_ptr<Cantera::Reaction> r2 = gas.reaction(2);


Cantera::ElementaryReaction* e1;

e1 = dynamic_cast<Cantera::ElementaryReaction*> (r2.get());

if(e1 ==0) 
{
std::cout<< "Null pointer on type casting to derived";
}

std::tr1::shared_ptr<Cantera::ElementaryReaction> new_reaction;
{
Cantera::Arrhenius new_rate(5.2e12,0.0,20.0);

 new_reaction.reset( new Cantera::ElementaryReaction( e1->reactants, e1->products, new_rate ) );
 }

gas.modifyReaction( 2, new_reaction );


gas.getNetProductionRates(&net_production_rates[0]);

for( unsigned int i = 0; i < 3; i++ )
	std::cout << "wdot[" << i << "] = " << net_production_rates[i] << std::endl;

//std::tr1::shared_ptr<Cantera::Reaction> m3(new Cantera::Reaction(2));



/*
Cantera::Reaction r1 = new Cantera::ElementaryReaction; 

Cantera::ElementaryReaction* e1;

e1 = dynamic_cast<Cantera::ElementaryReaction*> (r1);


if(e1 ==0) 
{
std::cout<< "Null pointer on type casting to derived";
}


if (Cantera::ElementaryReaction* e1 = dynamic_cast<Cantera::ElementaryReaction*> (m3))
std::cout << "Successful" << "\n";
*/

/*
std::shared_ptr<Cantera::Arrhenius> disply(new Cantera::Arrhenius::Arrhenius(&rdata));
Cantera::Arrhenius disply = new Cantera::Arrehenius::Arrhenius(&rdata);

Cantera::Arrhenius disply;

disply(Cantera::Arrhenius::Arrhenius(&rdata));

std::tr1::shared_ptr<Cantera::Reaction> rnew;

rnew.reset(new Cantera::Arrhenius(5.2e12,0.0,20.0));
gas.init();

gas.modifyReaction(2, rnew);

gas.finalize();


r.modifyReaction(size_t 2, shared_ptr<Reaction> rnew)
Cantera::Reaction mdy3;

std::shared_ptr<Reaction> rnew Cantera::Kinetics::reaction(size_t 2)


std::shared_ptr<Cantera::Reaction> rnew;

rnew.reset(new Cantera::Arrhenius(5.2e12,0.0,20.0));
gas.init();

gas.modifyReaction(2, rnew);

gas.finalize();

mdy3.checkReactionIndex( 2);

*/


