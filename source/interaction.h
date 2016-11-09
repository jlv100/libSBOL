#ifndef INTERACTION_INCLUDED
#define INTERACTION_INCLUDED

#include "identified.h"
#include "participation.h"

namespace sbol
{
    /// The Interaction class provides more detailed descriptionof how the FunctionalComponents are intended to work together. For example, this class can be used to represent different forms of genetic regulation (e.g., transcriptional activation or repression), processes from the central dogma of biology (e.g. transcription and translation), and other basic molecular interactions (e.g., non-covalent binding or enzymatic phosphorylation).
	class Interaction : public Identified
	{

	public:
        /// The types property is a REQUIRED set of URIs that describes the behavior represented by an Interaction.  The types property MUST contain one or more URIs that MUST identify terms from appropriate ontologies. It is RECOMMENDED that at least one of the URIs contained by the types property refer to a term from the occurring entity branch of the Systems Biology Ontology (SBO). (See http://www.ebi.ac.uk/sbo/main/) The following table provides a list of possible SBO terms for the types property and their corresponding URIs.
        /// | Type                 | URI for SBO Term                                 | LibSBOL symbol           |
        /// | :------------------- | :----------------------------------------------- | :----------------------- |
        /// | Biochemical Reaction | http://identifiers.org/biomodels.sbo/SBO:0000176 | SBO_BIOCHEMICAL_REACTION |
        /// | Inhibition           | http://identifiers.org/biomodels.sbo/SBO:0000169 | SBO_INHIBITION           |
        /// | Stimulation          | http://identifiers.org/biomodels.sbo/SBO:0000170 | SBO_STIMULATION          |
        /// | Genetic Production   | http://identifiers.org/biomodels.sbo/SBO:0000589 | SBO_GENETIC_PRODUCTION   |
        /// | Non-Covalent Binding | http://identifiers.org/biomodels.sbo/SBO:0000177 | SBO_NONCOVALENT_BINDING  |
        /// | Degradation          | http://identifiers.org/biomodels.sbo/SBO:0000179 | SBO_DEGRADATION          |
        /// | Control              | http://identifiers.org/biomodels.sbo/SBO:0000168 | SBO_CONTROL              |
		List<URIProperty> types;
        
        /// The participations property is an OPTIONAL and MAY contain a set of Participation objects, each of which identifies the roles that its referenced FunctionalComponent plays in the Interaction. Even though an Interaction generally contains at least one Participation, the case of zero Participation objects is allowed because it is plausible that a designer might want to specify that an Interaction will exist, even if its participants have not yet been determined.
		List<OwnedObject<Participation>> participations;
		
        /// Construct an Interaction
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param interaction_type A Systems Biology Ontology term that describes a biochemical interaction
        Interaction(std::string uri = DEFAULT_NS "/Interaction/example", std::string interaction_type = SBO_INTERACTION) : Interaction(SBOL_INTERACTION, uri, interaction_type) {};
        
//        Interaction(std::string uri_prefix, std::string display_id, std::string version, std::string interaction_type) : Interaction(SBOL_INTERACTION, uri_prefix, display_id, version, interaction_type) {};
        
        virtual ~Interaction() {};
        
	protected:
        Interaction(sbol_type type, std::string uri, std::string interaction_type) :
            Identified(type, uri),
            types(SBOL_TYPES, this, interaction_type),
            participations(SBOL_PARTICIPATIONS, this)
            {
            };
//        Interaction(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string interaction_type) :
//			Identified(type, uri_prefix, display_id, version),
//			types(SBOL_TYPES, this, interaction_type),
//			participations(SBOL_PARTICIPATIONS, this)
//			{
//            };
	};
}

#endif