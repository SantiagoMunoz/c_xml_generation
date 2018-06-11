from jinja2 import Environment, FileSystemLoader
import xml.etree.ElementTree as etree
import getopt
import sys

# Path data
template_prefix = 'templates'
config_prefix = 'config'
output_prefix = sys.argv[1]
# Load Jinja 2
file_loader = FileSystemLoader('.')
env = Environment(loader=file_loader,trim_blocks=True)

# Parse XML
tree= etree.parse('%s/op_sections.xml' % config_prefix)
m_root = tree.getroot()
m_opname = m_root.tag

op_dynamic_c = env.get_template('%s/base.c' % template_prefix)
output = op_dynamic_c.render(opname=m_opname,root=m_root)
filename = '%s/op_dynamic.c' % (output_prefix)
f = open(filename, 'w')
f.write(output)
op_dynamic = env.get_template('%s/base.h' % template_prefix)
output = op_dynamic.render(opname=m_opname,root=m_root)
filename = '%s/op_dynamic.h' % output_prefix
f = open(filename, 'w')
f.write(output)

