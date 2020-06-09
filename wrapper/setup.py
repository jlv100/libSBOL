from distutils.core import setup
setup(
        name='sbol',
        version='2.3.0',
        packages=['sbol'],
        package_data={'sbol': ['_libsbol.so','test/*/*','crispr_example.xml']}
)