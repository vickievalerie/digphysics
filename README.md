# Digital Toolkit for Physics Experiments

Content of this project:
* `arduinophysics` - Arduino Sketch to be uploaded to Arduino Uno board, which records all sensor data to SD Card (if present), and sends through serial
* `pyphysics` - Python utility script, including `pyexp.py` for running experiment through serial port
* `notebooks` - Jupyter notebooks with sample experiments and sample data (in `data` folder):
   - `KETL.ipynb` - Boiling Kettle
   - `Weather.ipynb` - Measuring length of light day
   - `FreeFall.ipynb` - Observing free fall via PhyPhox mobile app
   - `phyphox.py` is a small library for accessing PhyPhox exported experiment format
