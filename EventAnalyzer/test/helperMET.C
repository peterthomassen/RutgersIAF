void setupMETStudies(BaseHandler* handler)
{
  handler->addObjectVariable("PX",new ObjectVariableMethod("PX",&SignatureObject::Px));
  handler->addObjectVariable("PY",new ObjectVariableMethod("PY",&SignatureObject::Py));
  handler->addEventVariable("NVERTICES",new EventVariableN("NVERTICES","ALLVERTICES"));
  handler->addEventVariable("METPX",new EventVariableObjectVariableVector<double>("PX","MET"));
  handler->addEventVariable("METPY",new EventVariableObjectVariableVector<double>("PY","MET"));

  handler->addObjectVariable("isZ",new ObjectVariableValue<int>("pdgId",23));
  handler->addObjectVariable("status62", new ObjectVariableValue<int>("status",62));
  handler->addProduct("ZBOSONS","ALLMC");
  handler->addProductCut("ZBOSONS","isZ");
  handler->addProductCut("ZBOSONS","status62");


  handler->addEventVariable("ZPT",new EventVariableObjectVariableVector<double>("PT","ZBOSONS"));

}


