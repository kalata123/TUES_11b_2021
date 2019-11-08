import os
import platform


# Read properties file
def load_properties_file(file_name):
    if platform.system() == 'Windows':
        monitor_properties_path = os.path.join(os.environ.get('APPDATA'), 'mycompany', file_name)
    elif platform.system() == 'Linux':
        monitor_properties_path = os.path.join(os.environ.get('HOME'),
                            '.mycompany', file_name) or os.path.join('/etc', file_name)
    else:
        raise BaseException('Platform not supported: %s' % platform)

    return monitor_properties_path


path = load_properties_file("test.properties")
print("path: ", path)
