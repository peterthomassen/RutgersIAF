//////////////////////////////////////////////////////////
//
// RA7 specific event variables are defined here.
// These exclude RA7 objects which are mapped to the goodObjects products.
//
//////////////////////////////////////////////////////////

void addEventVariablesRA7(BaseHandler* handler,bool isMC = false, double mZ = 91, double zWidth = 10, double mW = 80.385)
{
 
  handler->addEventVariable("MINIISORA7FOMuons",     new EventVariableObjectVariableVector<double>("MINIISO","foRA7Muons"));
  handler->addEventVariable("MINIISORA7FOElectrons", new EventVariableObjectVariableVector<double>("MINIISO","foRA7Electrons"));

}
