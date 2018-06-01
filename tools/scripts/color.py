#create by PETS 12/10/2015
import os, sys, re, commands, subprocess, multiprocessing
import time, ctypes, shutil
class WTCW: # WindowsTerminalColourWrapper
    WRAPPERS = ['{', '}']
    
   # Constants from the Windows API: DO NOT CHANGE
    STD_INPUT_HANDLE  = -10;
    STD_OUTPUT_HANDLE = -11;
    STD_ERROR_HANDLE  = -12
    FG_BLUE = 0x01; FG_GREEN= 0x02; FG_RED  = 0x04; FG_INTENSITY = 0x08; FG_CYAN = 0x0B; FG_YELLOW = 0x0E;
    BG_BLUE = 0x10; BG_GREEN= 0x20; BG_RED  = 0x40; BG_INTENSITY = 0x80;
    colors = {'r': FG_RED, 'g':FG_GREEN, 'b':FG_BLUE, 'R':BG_RED, 'G':BG_GREEN, 'B':BG_BLUE, 'i':FG_INTENSITY, 'c':FG_CYAN, 'y':FG_YELLOW, 'I':BG_INTENSITY, 'w':FG_RED|FG_GREEN|FG_BLUE}
    
    def _get_csbi_attributes(self):
        # Based on IPython's winconsole.py, written by Alexander Belchenko
        import struct
        csbi = ctypes.create_string_buffer(22)
        res = ctypes.windll.kernel32.GetConsoleScreenBufferInfo(self.handle, csbi)
        assert res
        (bufx, bufy, curx, cury, wattr,
        left, top, right, bottom, maxx, maxy) = struct.unpack("hhhhHhhhhhh", csbi.raw)
        return wattr
    def __init__(self, stream, defColor = ''):
        self.stream = stream
        self.defColor = self._parseColor(defColor)
        self.handle = ctypes.windll.kernel32.GetStdHandle(self.STD_OUTPUT_HANDLE)
        self.reset = self._parseColor('rgb') # self._get_csbi_attributes()
    def __del__(self): self.resetColor()
    def __getattr__(self, attr): return getattr(self.stream, attr)
    def _parseColor(self, str): 
        colval = 0
        for c in str:
            if c.lower() == 'x': 
                self.resetColor()
                break
            colval |= self.colors[c]
        return colval
    def write(self, data):
        if self.defColor != 0: 
            self.setColour(defColor)
        parts = data.split(self.WRAPPERS[0])
        for part in parts:
            f = part.find(self.WRAPPERS[1])
            if f != -1:
                self.setColour(self._parseColor(part[0:f]))
                self.stream.write(part[f + len(self.WRAPPERS[1]):])
            else:
                self.stream.write(part)
            self.stream.flush()
        self.resetColor()
    def writeln(self, data): self.write(data + '\n')
    def setColour(self, color): ctypes.windll.kernel32.SetConsoleTextAttribute(self.handle, color)
    def resetColor(self): ctypes.windll.kernel32.SetConsoleTextAttribute(self.handle, self.reset)