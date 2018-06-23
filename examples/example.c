#include <stdlib.h>
#include <time.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>
#include "xml_dynamic.h"

int main()
{
    sample_structPtr_t m_sample_struct = sample_struct_new();
   
    time_t now = time(NULL); 
    sample_struct_set_time(m_sample_struct, &now);
    
    int i = 0; double d = 32.57;
    group1Ptr_t m_group1 = group1_new();
    group1_set_doubleNo(m_group1, &d);
    group1_set_intNo(m_group1,&i);
    for(i=0;i<2;i++){
        subGroupPtr_t m_sub = subGroup_new();
        subGroup_set_aString(m_sub, "sample string");
        group1_append_subGroup(m_group1, m_sub);
    }
    sample_struct_set_group1(m_sample_struct, m_group1);
        
    xmlNodePtr root_node = xmlNewNode(NULL, "document_root");
    sample_struct_build_xml(m_sample_struct, root_node); 
    xmlDocPtr xml_document = xmlNewDoc(NULL);
    xmlDocSetRootElement(xml_document, root_node);
    xmlSaveFile("sample_xml.xml",xml_document);
    
    xmlFreeDoc(xml_document);
    sample_struct_free(m_sample_struct);
    return 0;
}

