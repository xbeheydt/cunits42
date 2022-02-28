import ycm_core

VIMSPECTOR_HOME = '~/.vim/plugged/vimspector'

def Settings(**kwargs):
    if kwargs[ 'language' ] == 'json':
        return {
                'ls': {
                    'json': {
                        'schemas': [
                            {
                                'fileMatch': [ '.vimspector.json' ],
                                'url': f'file://{VIMSPECTOR_HOME}/docs/schema/vimspector.schema.json'
                                },
                            {
                                'fileMatch': [ '.gadgets.json', '.gadgets.d/*.json' ],
                                'url': f'file://{VIMSPECTOR_HOME}/docs/schema/gadgets.schema.json'
                                }
                            ]
                        }
                    }
                }
    return {
            'flags': [
                '-Wall', '-Werror', '-Wextra', '-g3',
                '-Iinclude', '-Isrc',
                ]
            }
