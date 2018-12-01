from shutil import which


def is_tool(name):
    return which(name) is not None


def tool_for_lang(lang):
    if lang == 'c':
        return 'gcc'
    elif lang == 'cpp':
        return 'g++'
    elif lang == 'go':
        return 'go'
    elif lang == 'js':
        return 'node'
    elif lang == 'py':
        return 'python'
    elif lang == 'rb':
        return 'ruby'
    elif lang == 'rs':
        return 'cargo'
    elif lang == 'sh':
        return 'bash'
    return lang
