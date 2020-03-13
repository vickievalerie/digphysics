import io
import pandas as pd
import zipfile

class PhyPhoxData:
    def __init__(self,filename):
        self.filename = filename
        
    def ReadString(self,name):
        archive = zipfile.ZipFile(self.filename, 'r')
        return archive.read(name+'.csv').decode('utf-8')
    
    def ReadDataFrame(self,name):
        return pd.read_csv(io.StringIO(self.ReadString(name)))