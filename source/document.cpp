#include "document.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <raptor2.h>

using namespace sbol;
using namespace std;

void TopLevel::addToDocument(Document& doc)
{
	doc.SBOLObjects[this->identity.get()] = this;
};

TopLevel& Document::getTopLevel(string uri)
{
    // @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return *(this->SBOLObjects[uri]);
};

raptor_world* Document::getWorld()
{
	// @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return (this->rdf_graph);
};

void Document::write()
{
	TopLevel *tl;
	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		std::cout << obj_i->first << obj_i->second->type << endl;
		tl = (obj_i->second);
		tl->getTypeURI();
	}
	tl->test();
	tl->getTypeURI();

};