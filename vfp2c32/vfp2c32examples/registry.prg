#INCLUDE vfp2c.h

CD (FULLPATH(JUSTPATH(SYS(16))))
SET LIBRARY TO vfp2c32.fll ADDITIVE
INITVFP2C32(VFP2C_INIT_ALL)

LOCAL lnKey, lnNewKey, lcValue, laError[1], loValues

&& creatine registry value's
TRY
	STORE 0 TO lnKey, lnNewKey
	&& one can only create direct subkey's of already open keys
	lnKey = OPENREGISTRYKEY(HKEY_LOCAL_MACHINE,'SOFTWARE')
	lnNewKey = CREATEREGISTRYKEY(lnKey,'YourFirmName') && create HKEY_LOCAL_MACHINE\SOFTWARE\YourFirmName
	WRITEREGISTRYKEY(lnNewKey,'Hello') && write Hello to the standard value
	WRITEREGISTRYKEY(lnNewKey,25,'SomeNumber')
	WRITEREGISTRYKEY(lnNewKey,34.345,'SomeFractional')
	WRITEREGISTRYKEY(lnNewKey,DATE(),'InstallDate')
	WRITEREGISTRYKEY(lnNewKey,DATETIME(),'InstallTime')
	WRITEREGISTRYKEY(lnNewKey,'A Multi_SZ_Value'+CHR(0)+'Second Value','SomeValue','',REG_MULTI_SZ)
	WRITEREGISTRYKEY(lnNewKey,'somebinary_variable_here_aasdfasdfkdjfkajdkfjalkjdfjadksfjlkajsdfj','SomeValue2','',REG_BINARY)
	WRITEREGISTRYKEY(lnNewKey,DATETIME(),'InstallTime 2')
CATCH TO loExp
	AERROREX('laError')
	DISPLAY MEMORY LIKE laError
FINALLY 
	IF lnNewKey != 0
		CLOSEREGISTRYKEY(lnNewKey)
	ENDIF
	IF lnKey != 0
		CLOSEREGISTRYKEY(lnKey)
	ENDIF
ENDTRY

SET STEP ON


&& store all values of a registry key to object properties
loValues = CREATEOBJECT('Empty')
?RegistryValuesToObject(HKEY_LOCAL_MACHINE,'SOFTWARE\YourFirmName',loValues)
?loValues.Standard
?loValues.SomeNumber
?loValues.InstallDate
?loValues.InstallTime
&& !!
?loValues.InstallTime_2
&& since value names can contain characters that are not valid for a property name
&& the function converts the names
&& the conversion scheme is as follows:
&& 1. if the value name starts with a digit an underscore (_) is prepended
&& 2. each invalid character (all expect 0-9, a-z, A-Z and _) is replaced with an underscore
&& examples:
&& "2.SomeName" -> "_2_SomeName"
&& "{HelloWorld}" -> "_HelloWorld_"


&& store a complete hive including subkeys into a object hierarchie
&& !!! don't use this for really large hives, e.g to retrieve the complete HKEY_LOCAL_MACHINE\SOFTWARE 
&& !!! FoxPro will run out of memory cause the maximum number of creatable objects will be reached
LOCAL loHive
loHive = CREATEOBJECT('Empty')
?RegistryHiveToObject(HKEY_CURRENT_USER,'Control Panel\Desktop',loHive)
?loHive.CaretWidth
?loHive.WindowMetrics.AppliedDPI
?loHive.WindowMetrics.ScrollHeight
?loHive.WindowMetrics.BorderWidth
&& ...
&& value/key names are converted to property names like described above

&& enumerate all subkeys of a key into an array
LOCAL laKeys[1], lnCount
lnCount = AREGISTRYKEYS('laKeys', HKEY_CURRENT_USER, 'SOFTWARE')
IF lnCount > 0
	DISPLAY MEMORY LIKE laKeys
ENDIF

&& enumerate all valuenames of a key into an array
LOCAL laValues[1]
lnCount = AREGISTRYVALUES('laValues',HKEY_CURRENT_USER, 'Environment')
IF lnCount > 0
	DISPLAY MEMORY LIKE laValues
ENDIF

&& enumerate all valuenames & values of a key into an array
LOCAL laValues[1]
lnCount = AREGISTRYVALUES('laValues',HKEY_CURRENT_USER, 'Environment', REG_ENUMVALUE)
IF lnCount > 0
	DISPLAY MEMORY LIKE laValues
ENDIF

&& enumerate all valuenames,values & valuetypes of a key into an array
LOCAL laValues[1]
lnCount = AREGISTRYVALUES('laValues',HKEY_CURRENT_USER, 'Environment', REG_ENUMTYPE + REG_ENUMVALUE)
IF lnCount > 0
	DISPLAY MEMORY LIKE laValues
ENDIF


&& reading a registry key in one line of code
TRY
	lcValue = READREGISTRYKEY(HKEY_LOCAL_MACHINE, ; && key is under HKEY_LOCAL_MACHINE hive 
							'', ; && return the "standard" value 
							'SOFTWARE\YourFirmName') && the path to the key
	? lcValue
	lcValue = READREGISTRYKEY(HKEY_LOCAL_MACHINE,'SomeNumber','SOFTWARE\YourFirmName')
	lcValue = READREGISTRYKEY(HKEY_LOCAL_MACHINE,'InstallDate','SOFTWARE\YourFirmName')
CATCH TO loExp
	AERROREX('laError')
	DISPLAY MEMORY LIKE laError
ENDTRY

&& reading several values from the same key, faster than above
TRY
	STORE 0 TO lnKey
	lnKey = OPENREGISTRYKEY(HKEY_LOCAL_MACHINE,'SOFTWARE\YourFirmName',KEY_READ) && open key for read only access
	lcValue = READREGISTRYKEY(lnKey) && read standard value
	lcValue = READREGISTRYKEY(lnKey,'SomeNumber')
	lcValue = READREGISTRYKEY(lnKey,'InstallDate')
CATCH TO loExp
	AERROREX('laError')
	DISPLAY MEMORY LIKE laError
FINALLY
	IF lnKey != 0
		CLOSEREGISTRYKEY(lnKey)
	ENDIF
ENDTRY