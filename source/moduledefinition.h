#ifndef MODULE_DEFINITION_INCLUDED
#define MODULE_DEFINITION_INCLUDED

#include "toplevel.h"
#include "module.h"
#include "component.h"
#include "interaction.h"

#include <string>

namespace sbol
{
    // Forward declaration of Model necessary for template instantiation of ModuleDefinition.models;
    class Model;
    
    /// The ModuleDefinition class represents a grouping of structural and functional entities in a biological design. The primary usage of this class is to assert the molecular interactions and abstract function of its child entities.
    class ModuleDefinition : public TopLevel
	{

	public:
        
        /// The roles property is an OPTIONAL set of URIs that clarifies the intended function of a ModuleDefinition. These URIs might identify descriptive biological roles, such as “metabolic pathway” and “signaling cascade,” but they can also identify identify “logical” roles, such as “inverter” or “AND gate”, or other abstract roles for describing the function of design. Interpretation of the meaning of such roles currently depends on the software tools that read and write them.
		List<URIProperty> roles;
        
        /// The modules property is OPTIONAL and MAY specify a set of Module objects contained by the ModuleDefinition. While the ModuleDefinition class is analogous to a specification sheet for a system of interacting biological elements, the Module class represents the occurrence of a particular subsystem within the system. Hence, this class allows a system design to include multiple instances of a subsystem, all defined by reference to the same ModuleDefinition. For example, consider the ModuleDefinition for a network of two-input repressor devices in which the particular repressors have not been chosen yet. This ModuleDefinition could contain multiple Module objects that refer to the same ModuleDefinition of an abstract two-input repressor device. Note that the set of relations between Module and ModuleDefinition objects is strictly acyclic.
		List<OwnedObject<Module>> modules;
        
        /// The interactions property is OPTIONAL and MAY specify a set of Interaction objects within the ModuleDefinition.  The Interaction class provides an abstract, machine-readable representation of entity behavior within a ModuleDefinition. Each Interaction contains Participation objects that indicate the roles of the FunctionalComponent objects involved in the Interaction.
        List<OwnedObject<Interaction>> interactions;
        
        /// The functionalComponents property is OPTIONAL and MAY specify a set of FunctionalComponent objects contained by the ModuleDefinition. Just as a Module represents an instance of a subsystem in the overall system represented by a ModuleDefinition, a FunctionalComponent represents an instance of a structural entity (represented by a ComponentDefinition) in the system. This concept allows a ModuleDefinition to assert different interactions for separate copies of the same structural entity if needed. For example, a ModuleDefinition might contain multiple FunctionalComponent objects that refer to the same promoter ComponentDefinition, but assert different interactions for these promoter copies based on their separate positions in another ComponentDefinition that represents the structure of the entire system.
		List<OwnedObject<FunctionalComponent>> functionalComponents;
        
        /// The models property is OPTIONAL and MAY specify a set of URI references to Model objects. Model objects are placeholders that link ModuleDefinition objects to computational models of any format. A ModuleDefinition object can link to more than one Model since each might encode system behavior in a different way or at a different level of detail.
        ReferencedObject models;
        
        /// Construct a ModuleDefinition
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a valid [Maven version string](http://maven.apache.org/).
        ModuleDefinition(std::string uri = DEFAULT_NS "/ModuleDefinition/example", std::string version = "1.0.0") : ModuleDefinition(SBOL_MODULE_DEFINITION, uri, version) {};
        
        /// Defines an output for a system module.
        /// @param output A ComponentDefinition that defines the output
        /// @return A FunctionalComponent that is derived from the argument ComponentDefinition and configured as this ModuleDefinition's output (it's direction property is set to SBOL_DIRECTION_OUT)
        FunctionalComponent& setOutput(ComponentDefinition& output);

        /// Defines an input for a system module.
        /// @param input A ComponentDefinition that defines the input
        /// @return A FunctionalComponent that is derived from the argument ComponentDefinition and configured as this ModuleDefinition's input (it's direction property is set to SBOL_DIRECTION_IN)
        FunctionalComponent& setInput(ComponentDefinition& input);
        
        virtual ~ModuleDefinition() {};

        /// Assemble a high-level ModuleDefinition from lower-level submodules. Autoconstructs Module objects in the process.
        /// @param list_of_modules A list of pointers to the submodule ModuleDefinitions
        void assemble(std::vector < ModuleDefinition* > list_of_modules);
        
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri
        ModuleDefinition(sbol_type sbol_type_uri, std::string uri, std::string version) :
            TopLevel(sbol_type_uri, uri, version),
            roles(SBOL_ROLES, this),
            models(SBOL_MODELS, SBOL_MODEL, this),
            functionalComponents(SBOL_FUNCTIONAL_COMPONENTS, this),
            modules(SBOL_MODULES, this),
            interactions(SBOL_INTERACTIONS, this)
            {
            };

	};
}

#endif