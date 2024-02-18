# -*- coding: utf-8 -*-
from setuptools import setup

packages = \
['pylib_test']

package_data = \
{'': ['*']}

install_requires = \
['pybind11>=2.8.0,<3.0.0', 'setuptools>=69.1.0,<70.0.0']

setup_kwargs = {
    'name': 'pylib-test',
    'version': '0.1.0',
    'description': '',
    'long_description': 'None',
    'author': 'Rustam Akhmadullin',
    'author_email': 'None',
    'maintainer': 'None',
    'maintainer_email': 'None',
    'url': 'None',
    'packages': packages,
    'package_data': package_data,
    'install_requires': install_requires,
    'python_requires': '>=3.10,<4.0',
}
from build import *
build(setup_kwargs)

setup(**setup_kwargs)
