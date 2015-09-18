#include "document.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <raptor2.h>

using namespace sbol;
using namespace std;

void Document::read(std::string filename)
{

}


void SBOLObject::serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world)
{
	cout << "Serializing object" << endl;

	// Check if there is an RDF graph associated with this SBOLObject.  Only TopLevel objects can be belong to SBOL Documents, so
	// only TopLevel objects have a valid back-pointer.
	//
	// The only other type of SBOL Object that can serialize besides TopLevel are objects
	// that form a composite with a TopLevel object.  In this case, the TopLevel object will pass the
	// pointer to the RDF graph to its composite objects

	if (doc)
	{
		sbol_world = doc->getWorld();
	}
	if (sbol_world)
	{
		// This RDF triple makes the following statement:
		// "This instance of an SBOL object belongs to class X"
		raptor_statement *triple = raptor_new_statement(sbol_world);
		std::string subject = identity.get();
		std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
		std::string object = type;

		triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
		triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
		triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

		cout << subject << predicate << object << endl;

		// Write the triples
		raptor_serializer_serialize_statement(sbol_serializer, triple);

		// Delete the triple 
		raptor_free_statement(triple);

		for (auto it = properties.begin(); it != properties.end(); ++it)
		{

			// This RDF triple makes the following statement:
			// "This SBOL object has a property called X and its value is Y"
			raptor_statement *triple2 = raptor_new_statement(sbol_world);

			//std::string new_predicate = (SBOL_URI "#" + it->first);
			std::string new_predicate = it->first;
			std::string new_object = it->second.front();

			triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
			triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)new_predicate.c_str());
			triple2->object = raptor_new_term_from_literal(sbol_world, (const unsigned char *)new_object.c_str(), NULL, NULL);

			cout << subject << new_predicate << new_object << endl;

			// Write the triples
			raptor_serializer_serialize_statement(sbol_serializer, triple2);

			// Delete the triple 
			raptor_free_statement(triple2);
		}

		// Serialize all properties corresponding to black diamonds in UML diagrams
		// RDF-XML list/container elements
		for (auto i = owned_objects.begin(); i != owned_objects.end(); ++i)
		{
			cout << "Serializing " << owned_objects.size() << " owned_objects" << endl;
			
			// Serialize each object in the object store that belongs to this property
			std::string property_name = i->first;
			vector<SBOLObject*> object_store = i->second;
			
			// This RDF triple makes the following statement:
			// "This instance of an SBOL object has property called X"
			raptor_statement *triple2 = raptor_new_statement(sbol_world);
			subject = identity.get();
			predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
			object = property_name;
			
			triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
			triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
			triple2->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());
			cout << subject << predicate << object << endl;

			// Write the triple2s
			raptor_serializer_serialize_statement(sbol_serializer, triple2);

			// Delete the triple 
			raptor_free_statement(triple2);

			int i_o = 0;
			for (auto o = object_store.begin(); o != object_store.end(); ++o)
			{
				SBOLObject* obj = *o;
				++i_o;
				cout << obj->type << endl;

				// This RDF triple makes the following statement:
				// "This instance of an SBOL object owns another SBOL object"
				raptor_statement *triple = raptor_new_statement(sbol_world);
				std::string subject = identity.get();
				std::string predicate = property_name;
				std::string object = obj->identity.get();
				
				//std::string subject = property_name;
				//std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#_" + std::to_string(i_o);
				//std::string object = obj->identity.get();

				//triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
				triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
				triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
				triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

				cout << subject << predicate << object << endl;

				// Write the triples
				raptor_serializer_serialize_statement(sbol_serializer, triple);

				// Delete the triple 
				raptor_free_statement(triple);

				// Recursive call to serialize child objects
				obj->serialize(sbol_serializer, sbol_world);
			}
		}
	}
}

void TopLevel::addToDocument(Document& doc)
{
	//doc.SBOLObjects[this->identity.get()] = this;
	doc.add(*this);
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

void Document::write(std::string filename)
{

	// Initialize raptor serializer
	FILE* fh = fopen(filename.c_str(), "wb");
	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	raptor_iostream* ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_serializer_start_to_iostream(sbol_serializer, NULL, ios);
	raptor_uri *sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI "#");
	raptor_uri *purl_uri = raptor_new_uri(world, (const unsigned char *)PURL_URI "#");
	const unsigned char *sbol_prefix = (const unsigned char *)"sbol";
	const unsigned char *purl_prefix = (const unsigned char *)"dcterms";
	raptor_namespace_stack *sbol_namespaces = raptor_new_namespaces(world, 0);
	raptor_namespace *sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	raptor_namespace *purl_namespace = raptor_new_namespace_from_uri(sbol_namespaces, purl_prefix, purl_uri, 1);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, purl_namespace);
	raptor_serializer_start_to_file_handle(sbol_serializer, NULL, fh);
	
	// Iterate through objects in document and serialize them
	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		obj_i->second->serialize(sbol_serializer);
	}

	// End serialization 
	raptor_serializer_serialize_end(sbol_serializer);
	raptor_free_serializer(sbol_serializer);
	raptor_free_iostream(ios);

};