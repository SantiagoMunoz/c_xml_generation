# c_xml_generation

A Jinja2 based C code generator for dynamic data storage and xml report production on embedded systems.

## What it is

This is code generation tool intended to ease the writing of repetitive xml generation code. I made this because I needed to generate several similar xml reports for a project and I saw it as an opportunity to save coding time and apply the DRY principle.

## Requeriments

You need to install *Python* (3.3 or later) and its package *Jinja2* in order to use the code generator.

The target C code relies on *libxml2* (2.6) for the report generation, so you will need to install that library too. Note that you dont actually need to do the code generation in your target machine.

## Usage

Let's take a look at the provided example struct definition.

	<struct name='sample_struct' type='root'>
	    <struct name='group1'>
	        <param dataType='double'>doubleNo</param>
	        <param dataType='int'>intNo</param>
	        <struct name='subGroup' type='multiple'>
	            <param dataType='char' length='32'>aString</param>
	            <param dataType='int' type='csv'>aCSV</param>
	        </struct>
	    </struct>
	    <param dataType='time_t'>time</param>
	</struct>

This struct contains a single parameter called 'time' and a node called 'group1' that holds 'doubleNo', 'intNo' and a variable number of 'subGroup' nodes each with their own children.

Now we will generate the code to get the functions that will allow us to build xml files with this format:
    
    $ python build.py example/example_xml_struct.xml example_xml_cogeden

The python script will take the 'example_xml_struct.xml' as an input structure defining the desired xml data and output the code to 'example_xml_codegen.h' and 'example_xml_codegen.c'. The functions look like this:

	typedef struct sample_struct_t* sample_structPtr_t;
	sample_structPtr_t sample_struct_new();
	void sample_struct_build_xml(sample_structPtr_t var, xmlNodePtr parent);
	/* ... */
	int group1_set_doubleNo(group1Ptr_t var, double *value);
	// ...and so on

We can use these functions to easily fill the data fields and generate the output xml:
	
	//Create structs and fill fields	
	time_t now = time(NULL); 
	int i = 0; double d = 32.57;
	sample_structPtr_t m_sample_struct = sample_struct_new();
	sample_struct_set_time(m_sample_struct, &now);
	group1Ptr_t m_group1 = group1_new();
	group1_set_doubleNo(m_group1, &d);
	group1_set_intNo(m_group1,&i);
	for(i=0;i<2;i++){
		subGroupPtr_t m_sub = subGroup_new();
		subGroup_set_aString(m_sub, "sample string");
		group1_append_subGroup(m_group1, m_sub);
	}
	sample_struct_set_group1(m_sample_struct, m_group1);

	//Generate XML
	xmlNodePtr root_node = xmlNewNode(NULL, "document_root");
	sample_struct_build_xml(m_sample_struct, root_node); 
	xmlDocPtr xml_document = xmlNewDoc(NULL);
	xmlDocSetRootElement(xml_document, root_node);
	xmlSaveFile("sample_xml.xml",xml_document);
	
	//Free resources. By freeing the root elements we also free all whildren recursively.	
	xmlFreeDoc(xml_document);
	sample_struct_free(m_sample_struct);

'sample_xml.xml' will look like this:

	<?xml version="1.0"?>
	<document_root>
	  <sample_struct>
	    <group1>
	      <doubleNo>32.570000</doubleNo>
	      <intNo>0</intNo>
	      <subGroup>
	        <aString>sample string</aString>
	        <aCSV/>
	      </subGroup>
	      <subGroup>
	        <aString>sample string</aString>
	        <aCSV/>
	      </subGroup>
	    </group1>
	    <time>2018-186T10:34:31.000Z</time>
	  </sample_struct>
	</document_root>

This example comes with a cmake build example:

    $ mkdir build;cd build
    $ cmake ../
    $ make
