# CommandLineCfg

The utility provides a command line interface to store and retrieve settings from a configuration file.

## Build

Use the make tool to build the program.  

```bash
make all
```

## Usage
The application supports following list of commands:

LIST - List all the keys and values of configuration file 

```bash
./CommandLineCfg LIST

*****************************************
*****************************************

Contact -> Prins Hendrikkade 164C 1011 TB Amsterdam, NL
DeviceCategory -> Access Control
Info -> Salto Group
Manufacturer -> Clay
Phone -> +31 203 034 280

*****************************************
*****************************************
```

GET - Retrieve value of the given key

```bash
./CommandLineCfg GET Manufacturer
Clay
```

SET - Store/update value of the given key

```bash
./CommandLineCfg SET DeviceCategory Security
OK

./CommandLineCfg GET DeviceCategory
Security
```

DELETE - Deletes the value corresponding to the provided key.
         The key stil exists in the config file with NULL value.

```bash
./CommandLineCfg DELETE DeviceCategory
OK

./CommandLineCfg GET DeviceCategory
(null)
```

ADD - Add a new keyvalue pair in the configuration file

```bash
./CommandLineCfg ADD MfgDate 14th March 2019
OK

./CommandLineCfg GET MfgDate
14th March 2019 
```

REMKEY- Removes the key and corresponding value from the configuration file.

```bash
./CommandLineCfg GET Phone
+31 203 034 280

./CommandLineCfg REMKEY Phone
OK

./CommandLineCfg GET Phone
Unable to find the indicated key
```



