#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include "sbolerror.h"
#include <string>

namespace sbol
{
    /// A class which contains global configuration variables for the libSBOL environment. Intended to be used like a static class, configuration variables are accessed through the `config' object.
    class Config
    {
    private:
        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like     signing a piece of paper.
        int SBOLCompliant; ///< Flag indicating whether to autoconstruct URI's consistent with SBOL's versioning scheme
        int catch_exceptions = 0;
    public:
        Config() :
        home(""),
        SBOLCompliant(1)
            {
            };
        void setHomespace(std::string ns);
        std::string getHomespace();
        int hasHomespace();
        void toggleSBOLCompliance();
        int isSBOLCompliant();
        void toggleExceptions();
        int exceptionsEnabled();


    };

    void setHomespace(std::string ns); ///< Set the default namespace for autocreation of URIs when a new SBOL object is created
    extern std::string getHomespace(); ///< Get the current default namespace for autocreation of URIs when a new SBOL object is created
    int hasHomespace();                ///< Checks if a valid default namespace has been defined
    void toggleSBOLCompliance();       ///< Enables SBOLCompliance, which simplifies creation of URIs in constructor calls
    int isSBOLCompliant();             ///< Checks if SBOLCompliance is enabled
    void toggleExceptions();
    int exceptionsEnabled();
    
    std::string randomIdentifier();
    std::string autoconstructURI();
    std::string constructNonCompliantURI(std::string uri);
    std::string constructCompliantURI(std::string sbol_type, std::string display_id, std::string version);
    std::string constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version);
    std::string getCompliantURI(std::string uri_prefix, std::string sbol_class_name, std::string display_id, std::string version);
    std::string getClassName(std::string type);
    std::string getNameSpace(std::string type);
}

#endif /* CONFIG_INCLUDED */