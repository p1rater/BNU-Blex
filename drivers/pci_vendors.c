/* pci_vendors.c – auto-generated from pci.ids (2503 vendors) */
#include "pci_vendors.h"

static const char vendor_names[] =
    "SafeNet (wrong ID)\n"
    "Allied Telesis, Inc (Wrong ID)\n"
    "Loongson Technology LLC\n"
    "Fn-Link Technology Limited\n"
    "PEAK-System Technik GmbH\n"
    "MICROCHIP\n"
    "Lockheed Martin-Marietta Corp\n"
    "Tiger Jet Network Inc. (Wrong ID)\n"
    "Hauppauge computer works Inc.\n"
    "Nebula Electronics Ltd.\n"
    "Silicon Image, Inc. (Wrong ID)\n"
    "Teles AG (Wrong ID)\n"
    "nCipher Security\n"
    "General Dynamics\n"
    "MIPS\n"
    "Dell (wrong ID)\n"
    "LevelOne\n"
    "Oxide Computer Company\n"
    "Dell (wrong ID)\n"
    "Compaq Computer Corporation\n"
    "Solidigm\n"
    "Hauppauge computer works Inc. (Wrong ID)\n"
    "Davicom Semiconductor, Inc. (Wrong ID)\n"
    "SpeedStream\n"
    "XFX Pine Group Inc. (Wrong ID)\n"
    "Hewlett-Packard Company (Wrong ID)\n"
    "ZyXEL Communications Corporation (Wrong ID)\n"
    "SK-Electronics Co., Ltd.\n"
    "ANDES\n"
    "TTTech Computertechnik AG (Wrong ID)\n"
    "SCM Microsystems, Inc.\n"
    "SIFIVE\n"
    "Dell Inc. (wrong ID)\n"
    "THEAD\n"
    "Lightelligence\n"
    "Dynalink\n"
    "LJMicro Co., Ltd\n"
    "Sapphire, Inc.\n"
    "Jingjia Microelectronics Co Ltd\n"
    "Xi'an Microelectronics Technology Institute\n"
    "Ubiquiti Networks, Inc.\n"
    "Wired Inc.\n"
    "D-Link System Inc\n"
    "T1042 [Freescale]\n"
    "Hantick\n"
    "VIA Technologies, Inc. (Wrong ID)\n"
    "BREA Technologies Inc\n"
    "Rhino Equipment Corp.\n"
    "Bachmann electronic GmbH\n"
    "Preferred Networks, Inc.\n"
    "Compaq Computer Corporation\n"
    "HaSoTec GmbH\n"
    "MediaTek Inc. (Wrong ID)\n"
    "SHF Communication Technologies AG\n"
    "Acrox Technologies Co., Ltd.\n"
    "Broadcom / LSI\n"
    "Kolter Electronic\n"
    "Advanced Micro Devices, Inc. [AMD/ATI]\n"
    "ULSI Systems\n"
    "VLSI Technology Inc\n"
    "Avance Logic Inc. [ALI]\n"
    "Reply Group\n"
    "NetFrame Systems Inc\n"
    "Epson\n"
    "Phoenix Technologies\n"
    "National Semiconductor Corporation\n"
    "Tseng Labs Inc\n"
    "AST Research Inc\n"
    "Weitek\n"
    "Video Logic, Ltd.\n"
    "Digital Equipment Corporation\n"
    "Micronics Computers Inc\n"
    "Cirrus Logic\n"
    "IBM\n"
    "LSI Logic Corp of Canada\n"
    "ICL Personal Systems\n"
    "SPEA Software AG\n"
    "Unisys Systems\n"
    "Elitegroup Computer Systems\n"
    "AT&T GIS (NCR)\n"
    "Vitesse Semiconductor\n"
    "Western Digital\n"
    "Maxim Integrated Products\n"
    "American Megatrends Inc.\n"
    "PictureTel\n"
    "Hitachi Computer Products\n"
    "OKI Electric Industry Co. Ltd.\n"
    "Advanced Micro Devices, Inc. [AMD]\n"
    "Trident Microsystems\n"
    "Beijing Dajia Internet Information Technology Co.\n"
    "Acer Incorporated [ALI]\n"
    "Dell\n"
    "Siemens Nixdorf IS\n"
    "LSI Logic\n"
    "Matrox Electronics Systems Ltd.\n"
    "Chips and Technologies\n"
    "Wyse Technology Inc.\n"
    "Olivetti Advanced Technology\n"
    "Toshiba America\n"
    "TMC Research\n"
    "Miro Computer Products AG\n"
    "Compaq\n"
    "NEC Corporation\n"
    "Framatome Connectors USA Inc.\n"
    "Comp. & Comm. Research Lab\n"
    "Future Domain Corp.\n"
    "Hitachi Micro Systems\n"
    "AMP, Inc\n"
    "Silicon Integrated Systems [SiS]\n"
    "Seiko Epson Corporation\n"
    "Tatung Corp. Of America\n"
    "Hewlett-Packard Company\n"
    "Solliday Engineering\n"
    "Synopsys/Logic Modeling Group\n"
    "Accelgraphics Inc.\n"
    "Computrend\n"
    "Micron\n"
    "ASUSTeK Computer Inc.\n"
    "Adaptec (formerly DPT)\n"
    "OPTi Inc.\n"
    "IPC Corporation, Ltd.\n"
    "Genoa Systems Corp\n"
    "Elsa AG\n"
    "Fountain Technologies, Inc.\n"
    "STMicroelectronics\n"
    "BusLogic\n"
    "Texas Instruments\n"
    "Sony Corporation\n"
    "Oak Technology, Inc\n"
    "Co-time Computer Ltd\n"
    "Winbond Electronics Corp\n"
    "Anigma, Inc.\n"
    "?Young Micro Systems\n"
    "Young Micro Systems\n"
    "Hitachi, Ltd\n"
    "Microchip Technology / SMSC\n"
    "ICL\n"
    "Motorola\n"
    "Electronics & Telecommunications RSH\n"
    "Kontron\n"
    "Promise Technology, Inc.\n"
    "Foxconn International, Inc.\n"
    "Wipro Infotech Limited\n"
    "Number 9 Computer Company\n"
    "Vtech Computers Ltd\n"
    "Infotronic America Inc\n"
    "United Microelectronics [UMC]\n"
    "I.I.T.\n"
    "Maspar Computer Corp\n"
    "Ocean Office Automation\n"
    "Alcatel\n"
    "Texas Microsystems\n"
    "PicoPower Technology\n"
    "Mitsubishi Electric\n"
    "Diversified Technology\n"
    "Mylex Corporation\n"
    "Aten Research Inc\n"
    "Apple Inc.\n"
    "Hynix Semiconductor\n"
    "Sequent Computer Systems\n"
    "DFI, Inc\n"
    "City Gate Development Ltd\n"
    "Daewoo Telecom Ltd\n"
    "Mitac\n"
    "GIT Co Ltd\n"
    "Yamaha Corporation\n"
    "NexGen Microsystems\n"
    "Advanced Integrations Research\n"
    "Chaintech Computer Co. Ltd\n"
    "QLogic Corp.\n"
    "Cyrix Corporation\n"
    "I-Bus\n"
    "NetWorth\n"
    "Gateway, Inc.\n"
    "LG Electronics [Lucky Goldstar Co. Ltd]\n"
    "LeadTek Research Inc.\n"
    "Interphase Corporation\n"
    "Data Technology Corporation\n"
    "Contaq Microsystems\n"
    "Supermac Technology\n"
    "EFA Corporation of America\n"
    "Forex Computer Corporation\n"
    "Parador\n"
    "J. Bond Computer Systems\n"
    "Cache Computer\n"
    "Microcomputer Systems (M) Son\n"
    "Data General Corporation\n"
    "SBS Technologies\n"
    "Oakleigh Systems Inc.\n"
    "Olicom\n"
    "Oracle/SUN\n"
    "Systemsoft\n"
    "Compro Computer Services, Inc.\n"
    "Intergraph Corporation\n"
    "Diamond Multimedia Systems\n"
    "National Instruments\n"
    "First International Computers [FIC]\n"
    "Silicon Image, Inc.\n"
    "Alacron\n"
    "Appian Technology\n"
    "Quantum Designs (H.K.) Ltd\n"
    "Samsung Electronics Co., Ltd\n"
    "Packard Bell\n"
    "Gemlight Computer Ltd.\n"
    "Megachips Corporation\n"
    "Zida Technologies Ltd.\n"
    "Brooktree Corporation\n"
    "Trigem Computer Inc.\n"
    "Meidensha Corporation\n"
    "Juko Electronics Ind. Co. Ltd\n"
    "Quantum Corporation\n"
    "Everex Systems Inc\n"
    "Globe Manufacturing Sales\n"
    "Smart Link Ltd.\n"
    "Informtech Industrial Ltd.\n"
    "Benchmarq Microelectronics\n"
    "Sierra Semiconductor\n"
    "Silicon Graphics Intl. Corp.\n"
    "ACC Microelectronics\n"
    "Digicom\n"
    "Honeywell IAC\n"
    "Winbond Electronics Corp / Symphony Labs\n"
    "Cornerstone Technology\n"
    "Micro Computer Systems Inc\n"
    "CardExpert Technology\n"
    "Cabletron Systems Inc\n"
    "Raytheon Company\n"
    "Databook Inc\n"
    "STB Systems Inc\n"
    "PLX Technology, Inc.\n"
    "Madge Networks\n"
    "3Com Corporation\n"
    "Standard Microsystems Corp [SMC]\n"
    "ULi Electronics Inc.\n"
    "Mitsubishi Electric Corp.\n"
    "Dapha Electronics Corporation\n"
    "Advanced Logic Research\n"
    "Surecom Technology\n"
    "Tseng Labs International Co.\n"
    "Most Inc\n"
    "Boca Research Inc.\n"
    "ICM Co., Ltd.\n"
    "Auspex Systems Inc.\n"
    "Samsung Semiconductors, Inc.\n"
    "Award Software International Inc.\n"
    "Xerox Corporation\n"
    "Rambus Inc.\n"
    "Media Vision\n"
    "Neomagic Corporation\n"
    "Dataexpert Corporation\n"
    "Fujitsu Microelectr., Inc.\n"
    "Omron Corporation\n"
    "Mai Logic Incorporated\n"
    "Advanced System Products, Inc\n"
    "Radius\n"
    "Fujitsu Limited.\n"
    "FuturePlus Systems Corp.\n"
    "Molex Incorporated\n"
    "Jabil Circuit Inc\n"
    "Hualon Microelectronics\n"
    "Autologic Inc.\n"
    "Cetia\n"
    "BCM Advanced Research\n"
    "Advanced Peripherals Labs\n"
    "Macronix, Inc. [MXIC]\n"
    "Compaq IPG-Austin\n"
    "Rohm LSI Systems, Inc.\n"
    "CERN/ECP/EDU\n"
    "Evans & Sutherland\n"
    "NVIDIA Corporation\n"
    "Emulex Corporation\n"
    "Integrated Micro Solutions Inc.\n"
    "Tekram Technology Co.,Ltd.\n"
    "Aptix Corporation\n"
    "Tundra Semiconductor Corp.\n"
    "Tandem Computers\n"
    "Micro Industries Corporation\n"
    "Gainbery Computer Products Inc.\n"
    "Vadem\n"
    "Applied Micro Circuits Corp.\n"
    "Alps Electric Co., Ltd.\n"
    "Integraphics\n"
    "Artists Graphics\n"
    "Realtek Semiconductor Co., Ltd.\n"
    "Ascii Corporation\n"
    "Xilinx Corporation\n"
    "Racore Computer Products, Inc.\n"
    "Peritek Corporation\n"
    "Tyan Computer\n"
    "Achme Computer, Inc.\n"
    "Alaris, Inc.\n"
    "S-MOS Systems, Inc.\n"
    "NKK Corporation\n"
    "Creative Electronic Systems SA\n"
    "Matsushita Electric Industrial Co., Ltd.\n"
    "Altos India Ltd\n"
    "PC Direct\n"
    "Truevision\n"
    "Thesys Gesellschaft fuer Mikroelektronik mbH\n"
    "I-O Data Device, Inc.\n"
    "Soyo Computer, Inc\n"
    "Fast Multimedia AG\n"
    "NCube\n"
    "Jazz Multimedia\n"
    "Initio Corporation\n"
    "Creative Labs\n"
    "HighPoint Technologies, Inc.\n"
    "RasterOps Corp.\n"
    "Sigma Designs, Inc.\n"
    "VIA Technologies, Inc.\n"
    "Stratus Computers\n"
    "Proteon, Inc.\n"
    "Cogent Data Technologies, Inc.\n"
    "Siemens AG\n"
    "Chromatic Research Inc.\n"
    "Mini-Max Technology, Inc.\n"
    "Znyx Advanced Systems\n"
    "CPU Technology\n"
    "Ross Technology\n"
    "Powerhouse Systems\n"
    "Santa Cruz Operation\n"
    "Osicom Technologies Inc\n"
    "Accton Technology Corporation\n"
    "Atmel Corporation\n"
    "3D Labs\n"
    "Data Translation\n"
    "Datacube, Inc\n"
    "Berg Electronics\n"
    "ICP Vortex Computersysteme GmbH\n"
    "Efficient Networks, Inc\n"
    "Teledyne Electronic Systems\n"
    "Tricord Systems Inc.\n"
    "Microsemi / PMC / IDT\n"
    "Eldec\n"
    "Precision Digital Images\n"
    "Dell EMC\n"
    "Zilog\n"
    "Multi-tech Systems, Inc.\n"
    "Excellent Design, Inc.\n"
    "Leutron Vision AG\n"
    "Eurocore\n"
    "Vigra\n"
    "FORE Systems Inc\n"
    "Firmworks\n"
    "Hermes Electronics Company, Ltd.\n"
    "Heidelberger Druckmaschinen AG\n"
    "Zenith Data Systems\n"
    "Ravicad\n"
    "Infomedia Microelectronics Inc.\n"
    "Dalsa Inc.\n"
    "Computervision\n"
    "Philips Semiconductors\n"
    "Mitel Corp.\n"
    "Dialogic Corporation\n"
    "Mercury Computer Systems\n"
    "FUJIFILM Business Innovation Corp.\n"
    "Momentum Data Systems\n"
    "Cisco Systems Inc\n"
    "Ziatech Corporation\n"
    "Dynamic Pictures, Inc\n"
    "FWB Inc\n"
    "Network Computing Devices\n"
    "Cyclone Microsystems, Inc.\n"
    "Leading Edge Products Inc\n"
    "Sanyo Electric Co - Computer Engineering Dept\n"
    "Equinox Systems, Inc.\n"
    "Intervoice Inc\n"
    "Crest Microsystem Inc\n"
    "Alliance Semiconductor Corporation\n"
    "NetPower, Inc\n"
    "Cincinnati Milacron\n"
    "Workbit Corporation\n"
    "Force Computers\n"
    "Interface Corp\n"
    "SysKonnect\n"
    "Win System Corporation\n"
    "VMIC\n"
    "Canopus Co., Ltd\n"
    "Annabooks\n"
    "IC Corporation\n"
    "Nikon Systems Inc\n"
    "Digi International\n"
    "Thinking Machines Corp\n"
    "JAE Electronics Inc.\n"
    "Megatek\n"
    "Land Win Electronic Corp\n"
    "Melco Inc\n"
    "Pine Technology Ltd\n"
    "Periscope Engineering\n"
    "Avsys Corporation\n"
    "Voarx R & D Inc\n"
    "MuTech Corporation\n"
    "Harlequin Ltd\n"
    "Parallax Graphics\n"
    "Photron Ltd.\n"
    "Xircom\n"
    "Peer Protocols Inc\n"
    "Maxtor Corporation\n"
    "Megasoft Inc\n"
    "PFU Limited\n"
    "OA Laboratory Co Ltd\n"
    "Rendition\n"
    "Advanced Peripherals Technologies\n"
    "Imagraph Corporation\n"
    "Broadcom\n"
    "Mutoh Industries Inc\n"
    "Thine Electronics Inc\n"
    "Centre for Development of Advanced Computing\n"
    "Luminex Software, Inc.\n"
    "Connectware Inc\n"
    "Intelligent Resources Integrated Systems\n"
    "Martin-Marietta\n"
    "Electronics for Imaging\n"
    "Workstation Technology\n"
    "Inventec Corporation\n"
    "Loughborough Sound Images Plc\n"
    "Altera Corporation\n"
    "Adobe Systems, Inc\n"
    "Bridgeport Machines\n"
    "Mitron Computer Inc.\n"
    "SBE Incorporated\n"
    "Silicon Engineering\n"
    "Alfa, Inc.\n"
    "Toshiba Corporation\n"
    "A-Trend Technology\n"
    "L G Electronics, Inc.\n"
    "ATTO Technology, Inc.\n"
    "Becton & Dickinson\n"
    "T/R Systems\n"
    "Integrated Circuit Systems\n"
    "Ricoh Co Ltd\n"
    "Telmatics International\n"
    "Fujikura Ltd\n"
    "Forks Inc\n"
    "Dataworld International Ltd\n"
    "D-Link System Inc\n"
    "Advanced Technology Laboratories, Inc.\n"
    "Shima Seiki Manufacturing Ltd.\n"
    "Matsushita Electronics Co Ltd\n"
    "Hilevel Technology\n"
    "Hypertec Pty Limited\n"
    "Corollary, Inc\n"
    "BitFlow Inc\n"
    "Hermstedt GmbH\n"
    "Green Logic\n"
    "Tripace\n"
    "Artop Electronic Corp\n"
    "Densan Company Ltd\n"
    "Zeitnet Inc.\n"
    "Toucan Technology\n"
    "Ratoc System Inc\n"
    "Hytec Electronics Ltd\n"
    "Gage Applied Sciences, Inc.\n"
    "Lambda Systems Inc\n"
    "Attachmate Corporation\n"
    "Mind Share, Inc.\n"
    "Omega Micro Inc.\n"
    "Information Technology Inst.\n"
    "Bug, Inc. Sapporo Japan\n"
    "Fujitsu Microelectronics Ltd.\n"
    "Bull HN Information Systems\n"
    "Convex Computer Corporation\n"
    "Hamamatsu Photonics K.K.\n"
    "Sierra Research and Technology\n"
    "Deuretzbacher GmbH & Co. Eng. KG\n"
    "Barco Graphics NV\n"
    "Microunity Systems Eng. Inc\n"
    "Pure Data Ltd.\n"
    "Power Computing Corp.\n"
    "Systech Corp.\n"
    "InnoSys Inc.\n"
    "Actel\n"
    "Marvell Technology Group Ltd.\n"
    "Canon Information Systems Research Aust.\n"
    "Lite-On Communications Inc\n"
    "Aztech System Ltd\n"
    "Avid Technology Inc.\n"
    "V3 Semiconductor Inc.\n"
    "Apricot Computers\n"
    "Eastman Kodak\n"
    "Barr Systems Inc.\n"
    "Leitch Technology International\n"
    "Radstone Technology Plc\n"
    "United Video Corp\n"
    "Motorola\n"
    "XPoint Technologies, Inc\n"
    "Pathlight Technology Inc.\n"
    "Videotron Corp\n"
    "Pyramid Technology\n"
    "Network Peripherals Inc\n"
    "Pinnacle Systems Inc.\n"
    "International Microcircuits Inc\n"
    "Astrodesign, Inc.\n"
    "Hewlett Packard\n"
    "LSI Corporation\n"
    "Sand Microelectronics\n"
    "NEC Corporation\n"
    "Document Technologies, Inc\n"
    "Shiva Corporation\n"
    "Dainippon Screen Mfg. Co. Ltd\n"
    "D.C.M. Data Systems\n"
    "Dolphin Interconnect Solutions AS\n"
    "Magma\n"
    "IBEX Technology Co., Ltd.\n"
    "Specialix Research Ltd.\n"
    "Michels & Kleberhoff Computer GmbH\n"
    "HAL Computer Systems, Inc.\n"
    "Netaccess\n"
    "Pioneer Electronic Corporation\n"
    "Lockheed Martin Federal Systems-Manassas\n"
    "Auravision\n"
    "Intercom Inc.\n"
    "Trancell Systems Inc\n"
    "Analog Devices\n"
    "Ikon Corporation\n"
    "Tekelec Telecom\n"
    "Trenton Technology, Inc.\n"
    "Image Technologies Development\n"
    "TEC Corporation\n"
    "Novell\n"
    "Sega Enterprises Ltd\n"
    "Questra Corporation\n"
    "Crosfield Electronics Limited\n"
    "Zoran Corporation\n"
    "New Wave PDG\n"
    "Cray Communications A/S\n"
    "GEC Plessey Semi Inc.\n"
    "Samsung Information Systems America\n"
    "Quicklogic Corporation\n"
    "Second Wave Inc\n"
    "IIX Consulting\n"
    "Mitsui-Zosen System Research\n"
    "Toshiba America, Elec. Company\n"
    "Digital Processing Systems Inc.\n"
    "Highwater Designs Ltd.\n"
    "Elsag Bailey\n"
    "Formation Inc.\n"
    "Coreco Inc\n"
    "Mediamatics\n"
    "Dome Imaging Systems Inc\n"
    "Nicolet Technologies B.V.\n"
    "Compu-Shack\n"
    "Symbios Logic Inc\n"
    "Picture Tel Japan K.K.\n"
    "Keithley Metrabyte\n"
    "Kinetic Systems Corporation\n"
    "Computing Devices International\n"
    "Compex\n"
    "Scientific Atlanta\n"
    "Microchip Technology\n"
    "I-Cube Inc\n"
    "Kasan Electronics Company, Ltd.\n"
    "Datel Inc\n"
    "Silicon Magic\n"
    "High Street Consultants\n"
    "Pepperl+Fuchs\n"
    "Scion Corporation\n"
    "CSS Corporation\n"
    "Vista Controls Corp\n"
    "Network General Corp.\n"
    "Bayer Corporation, Agfa Division\n"
    "Lattice Semiconductor Corporation\n"
    "Array Corporation\n"
    "Amdahl Corporation\n"
    "Parsytec GmbH\n"
    "SCI Systems Inc\n"
    "Synaptel\n"
    "Adaptive Solutions\n"
    "Technical Corp.\n"
    "Compression Labs, Inc.\n"
    "Cyclades Corporation\n"
    "Essential Communications\n"
    "Hyperparallel Technologies\n"
    "Braintech Inc\n"
    "Applied Intelligent Systems, Inc.\n"
    "Performance Technologies, Inc.\n"
    "Interware Co., Ltd\n"
    "Purup Prepress A/S\n"
    "O2 Micro, Inc.\n"
    "Hybricon Corp.\n"
    "First Virtual Corporation\n"
    "3Dfx Interactive, Inc.\n"
    "Advanced Telecommunications Modules\n"
    "Nippon Texaco., Ltd\n"
    "LiPPERT ADLINK Technology GmbH\n"
    "CSPI\n"
    "Arcus Technology, Inc.\n"
    "Ariel Corporation\n"
    "Contec Co., Ltd\n"
    "Ancor Communications, Inc.\n"
    "Artesyn Communication Products\n"
    "Interactive Images\n"
    "Power I/O, Inc.\n"
    "EIZO Rugged Solutions\n"
    "Norsk Elektro Optikk A/S\n"
    "Data Kinesis Inc.\n"
    "Integrated Telecom\n"
    "LG Industrial Systems Co., Ltd\n"
    "Sican GmbH\n"
    "Aztech System Ltd\n"
    "Xyratex\n"
    "Andrew Corporation\n"
    "Fishcamp Engineering\n"
    "Woodward McCoach, Inc.\n"
    "GPT Limited\n"
    "Bus-Tech, Inc.\n"
    "SMART Modular Technologies\n"
    "Sigma Designs Corporation\n"
    "Alta Technology Corporation\n"
    "Adtran\n"
    "3DO Company\n"
    "Visicom Laboratories, Inc.\n"
    "Seeq Technology, Inc.\n"
    "Century Systems, Inc.\n"
    "Engineering Design Team, Inc.\n"
    "Simutech, Inc.\n"
    "LSI Logic\n"
    "Marathon Technologies Corp.\n"
    "DSC Communications\n"
    "JNI Corporation\n"
    "Delphax\n"
    "AVM GmbH\n"
    "A.P.D., S.A.\n"
    "Dipix Technologies, Inc.\n"
    "Xylon Research, Inc.\n"
    "Central Data Corporation\n"
    "Samsung Electronics Co., Ltd.\n"
    "AEG Electrocom GmbH\n"
    "SBS/Greenspring Modular I/O\n"
    "Solitron Technologies, Inc.\n"
    "Stallion Technologies, Inc.\n"
    "Cylink\n"
    "Infortrend Technology, Inc.\n"
    "Hitachi Microcomputer System Ltd\n"
    "VLSI Solutions Oy\n"
    "Guzik Technical Enterprises\n"
    "Linear Systems Ltd.\n"
    "Optibase Ltd\n"
    "Perceptive Solutions, Inc.\n"
    "Vertex Networks, Inc.\n"
    "Gilbarco, Inc.\n"
    "Allied Telesis\n"
    "ABB Power Systems\n"
    "Asix Electronics Corporation\n"
    "Aurora Technologies, Inc.\n"
    "ESS Technology\n"
    "Specialvideo Engineering SRL\n"
    "Concurrent Technologies, Inc.\n"
    "Intersil Corporation\n"
    "Matsushita-Kotobuki Electronics Industries, Ltd.\n"
    "ES Computer Company, Ltd.\n"
    "Sonic Solutions\n"
    "Aval Nagasaki Corporation\n"
    "Casio Computer Co., Ltd.\n"
    "Microdyne Corporation\n"
    "S. A. Telecommunications\n"
    "Tektronix\n"
    "Thales\n"
    "Lexmark International, Inc.\n"
    "Adax, Inc.\n"
    "Northern Telecom\n"
    "Splash Technology, Inc.\n"
    "Sumitomo Metal Industries, Ltd.\n"
    "Silicon Motion, Inc.\n"
    "Olympus Optical Co., Ltd.\n"
    "GW Instruments\n"
    "Telematics International\n"
    "Hughes Network Systems\n"
    "Ensoniq\n"
    "Network Appliance Corporation\n"
    "Switched Network Technologies, Inc.\n"
    "Comstream\n"
    "Transtech Parallel Systems Ltd.\n"
    "Transmeta Corporation\n"
    "Rockwell International\n"
    "Pixera Corporation\n"
    "Crosspoint Solutions, Inc.\n"
    "Vela Research\n"
    "Winnov, L.P.\n"
    "Fujifilm\n"
    "Photoscript Group Ltd.\n"
    "Yokogawa Electric Corporation\n"
    "Davicom Semiconductor, Inc.\n"
    "Integrated Technology Express, Inc.\n"
    "Sahara Networks, Inc.\n"
    "Platform Technologies, Inc.\n"
    "Mazet GmbH\n"
    "M-Pact, Inc.\n"
    "Timestep Corporation\n"
    "AVC Technology, Inc.\n"
    "Asante Technologies, Inc.\n"
    "Transwitch Corporation\n"
    "Retix Corporation\n"
    "G2 Networks, Inc.\n"
    "Hoontech Corporation/Samho Multi Tech Ltd.\n"
    "Tateno Dennou, Inc.\n"
    "Sord Computer Corporation\n"
    "NCS Computer Italia\n"
    "Tritech Microelectronics Inc\n"
    "Media Reality Technology\n"
    "Rhetorex, Inc.\n"
    "Imagenation Corporation\n"
    "Kofax Image Products\n"
    "Holco Enterprise Co, Ltd/Shuttle Computer\n"
    "Spellcaster Telecommunications Inc.\n"
    "Knowledge Technology Lab.\n"
    "VMetro, inc.\n"
    "Image Access\n"
    "Jaycor\n"
    "Compcore Multimedia, Inc.\n"
    "Victor Company of Japan, Ltd.\n"
    "OEC Medical Systems, Inc.\n"
    "Allen-Bradley Company\n"
    "Simpact Associates, Inc.\n"
    "Newgen Systems Corporation\n"
    "Lucent Technologies\n"
    "NTT Innovative Devices Corporation\n"
    "Vision Dynamics Ltd.\n"
    "Scalable Networks, Inc.\n"
    "AMO GmbH\n"
    "News Datacom\n"
    "Xiotech Corporation\n"
    "SDL Communications, Inc.\n"
    "YUAN High-Tech Development Co., Ltd.\n"
    "Measurex Corporation\n"
    "Multidata GmbH\n"
    "Alteon Networks Inc.\n"
    "TDK Corporation\n"
    "Jorge Scientific Corp\n"
    "GammaLink\n"
    "General Signal Networks\n"
    "Inter-Face Co Ltd\n"
    "FutureTel Inc\n"
    "Granite Systems Inc.\n"
    "Natural Microsystems\n"
    "Cognex Corporation\n"
    "Korg\n"
    "3Com Corp, Modem Division\n"
    "BittWare, Inc.\n"
    "Nippon Unisoft Corporation\n"
    "Array Microsystems\n"
    "Computerm Corp.\n"
    "Anchor Chips Inc.\n"
    "Fujifilm Microdevices\n"
    "Infimed\n"
    "GMM Research Corp\n"
    "Mentec Limited\n"
    "Holtek Microelectronics Inc\n"
    "Connect Tech Inc\n"
    "Picture Elements Incorporated\n"
    "Mitani Corporation\n"
    "Dialogic Corp\n"
    "G Force Co, Ltd\n"
    "Gigi Operations\n"
    "Integrated Computing Engines\n"
    "Antex Electronics Corporation\n"
    "Pluto Technologies International\n"
    "Aims Lab\n"
    "Netspeed Inc.\n"
    "Prophet Systems, Inc.\n"
    "GDE Systems, Inc.\n"
    "PSITech\n"
    "NVidia / SGS Thomson (Joint Venture)\n"
    "Vingmed Sound A/S\n"
    "Ulticom (Formerly DGM&S)\n"
    "Equator Technologies Inc\n"
    "Analogic Corp\n"
    "Biotronic SRL\n"
    "Pericom Semiconductor\n"
    "Aculab PLC\n"
    "True Time Inc.\n"
    "Annapolis Micro Systems, Inc\n"
    "Symicron Computer Communication Ltd.\n"
    "Management Graphics\n"
    "Rainbow Technologies\n"
    "SBS Technologies Inc\n"
    "Chase Research\n"
    "Nintendo Co, Ltd\n"
    "Datum Inc. Bancomm-Timing Division\n"
    "Imation Corp - Medical Imaging Systems\n"
    "Brooktrout Technology Inc\n"
    "Apex Semiconductor Inc\n"
    "Cirel Systems\n"
    "Sunsgroup Corporation\n"
    "Crisc Corp\n"
    "GE Spacenet\n"
    "Zuken\n"
    "Aureal Semiconductor\n"
    "3A International, Inc.\n"
    "Optivision Inc.\n"
    "Orange Micro\n"
    "Vienna Systems\n"
    "Pentek\n"
    "Sorenson Vision Inc\n"
    "Gammagraphx, Inc.\n"
    "Radstone Technology\n"
    "Megatel\n"
    "Forks\n"
    "Dawson France\n"
    "Cognex\n"
    "Electronic Design GmbH\n"
    "Four Fold Ltd\n"
    "Spectrum Signal Processing\n"
    "Capital Equipment Corp\n"
    "I2S\n"
    "ESD Electronic System Design GmbH\n"
    "Lexicon\n"
    "Harman International Industries Inc\n"
    "Computer Sciences Corp\n"
    "Innovative Integration\n"
    "Juniper Networks\n"
    "Netphone, Inc\n"
    "Duet Technologies\n"
    "Measurement Computing\n"
    "Jato Technologies Inc.\n"
    "AB Semiconductor Ltd\n"
    "Mitsubishi Electric Microcomputer\n"
    "Colorgraphic Communications Corp\n"
    "Ambex Technologies, Inc\n"
    "Accelerix Inc\n"
    "Yamatake-Honeywell Co. Ltd\n"
    "Advanet Inc\n"
    "Gespac\n"
    "Videoserver, Inc\n"
    "Acuity Imaging, Inc\n"
    "Yaskawa Electric Co.\n"
    "Wavesat\n"
    "Teradyne Inc\n"
    "ADMtek\n"
    "Packet Engines Inc.\n"
    "Fortemedia, Inc\n"
    "Finisar Corp.\n"
    "Nippon Electro-Sensory Devices Corp\n"
    "Sysmic, Inc.\n"
    "Xinex Networks Inc\n"
    "Siig Inc\n"
    "Crypto AG\n"
    "Arcobel Graphics BV\n"
    "MTT Co., Ltd\n"
    "Dome Inc\n"
    "Sphere Communications\n"
    "Salix Technologies, Inc\n"
    "Seachange international\n"
    "Voss scientific\n"
    "quadrant international\n"
    "Productivity Enhancement\n"
    "Microcom Inc.\n"
    "Broadband Technologies\n"
    "Micrel Inc\n"
    "Integrated Silicon Solution, Inc.\n"
    "MMC Networks\n"
    "RadiSys Corporation\n"
    "Micro Memory\n"
    "Redcreek Communications, Inc\n"
    "Videomail, Inc\n"
    "Third Planet Publishing\n"
    "BT Electronics\n"
    "Vtel Corp\n"
    "Softcom Microsystems\n"
    "Holontech Corp\n"
    "SS Technologies\n"
    "Virtual Computer Corp\n"
    "SCM Microsystems\n"
    "Atalla Corp\n"
    "Kyoto Microcomputer Co\n"
    "Promax Systems Inc\n"
    "Phylon Communications Inc\n"
    "Micron Technology Inc\n"
    "Arescom Inc\n"
    "Odetics\n"
    "Sumitomo Electric Industries, Ltd.\n"
    "DTC Technology Corp.\n"
    "ARK Research Corp.\n"
    "Chori Joho System Co. Ltd\n"
    "PCTel Inc\n"
    "CSTI\n"
    "Algo System Co Ltd\n"
    "Systec Co. Ltd\n"
    "Sonix Inc\n"
    "dbeeSet Technology\n"
    "Dwave System Inc\n"
    "Kratos Analytical Ltd\n"
    "The Logical Co\n"
    "Prisa Networks\n"
    "Brainboxes Ltd\n"
    "Giganet Inc\n"
    "Quatech Inc\n"
    "ABB Network Partner AB\n"
    "Sealevel Systems Inc\n"
    "I-Data International A-S\n"
    "Meinberg Funkuhren\n"
    "Soliton Systems K.K.\n"
    "Fujifacom Corporation\n"
    "Phoenix Technology Ltd\n"
    "ATM Communications Inc\n"
    "Hypercope GmbH\n"
    "Teijin Seiki Co. Ltd\n"
    "Hitachi Zosen Corporation\n"
    "Skyware Corporation\n"
    "Digigram\n"
    "High Soft Tech\n"
    "Kawasaki Steel Corporation\n"
    "Adtek System Science Co Ltd\n"
    "Gigalabs Inc\n"
    "Applied Magic Inc\n"
    "ATL Products\n"
    "CNet Technology Inc\n"
    "Silicon Vision Inc\n"
    "Silicom Ltd.\n"
    "Argosystems Inc\n"
    "LMC\n"
    "Electronic Equipment Production & Distribution GmbH\n"
    "Telemann Co. Ltd\n"
    "Asahi Kasei Microsystems Co Ltd\n"
    "Mark of the Unicorn Inc\n"
    "PPT Vision\n"
    "Iwatsu Electric Co Ltd\n"
    "Dynachip Corporation\n"
    "Patriot Scientific Corporation\n"
    "Japan Satellite Systems Inc\n"
    "Sanritz Automation Co Ltd\n"
    "Brains Co. Ltd\n"
    "Marian - Electronic & Software\n"
    "Controlnet Inc\n"
    "Reality Simulation Systems Inc\n"
    "Netgear\n"
    "Video Domain Technologies\n"
    "Systran Corp\n"
    "Hitachi Information Technology Co Ltd\n"
    "Applicom International\n"
    "Fusion Micromedia Corp\n"
    "Tokimec Inc\n"
    "Silicon Reality\n"
    "Future Techno Designs pte Ltd\n"
    "Basler GmbH\n"
    "Patapsco Designs Inc\n"
    "Concept Development Inc\n"
    "Development Concepts Inc\n"
    "Medialight Inc\n"
    "Moxa Technologies Co Ltd\n"
    "Level One Communications\n"
    "Ambicom Inc\n"
    "Cipher Systems Inc\n"
    "Cologne Chip Designs GmbH\n"
    "Clarion co. Ltd\n"
    "Rios systems Co Ltd\n"
    "Alacritech Inc\n"
    "Mediasonic Multimedia Systems Ltd\n"
    "Quantum 3d Inc\n"
    "EPL limited\n"
    "Media4\n"
    "Aethra s.r.l.\n"
    "Crystal Group Inc\n"
    "Kawasaki Heavy Industries Ltd\n"
    "Ositech Communications Inc\n"
    "Hifn Inc.\n"
    "Rascom Inc\n"
    "Audio Digital Imaging Inc\n"
    "Videonics Inc\n"
    "Teles AG\n"
    "Exar Corp.\n"
    "Siemens Medical Systems, Ultrasound Group\n"
    "Broadband Networks Inc\n"
    "Arcom Control Systems Ltd\n"
    "Motion Media Technology Ltd\n"
    "Nexus Inc\n"
    "ALD Technology Ltd\n"
    "T.Sqware\n"
    "Maxspeed Corp\n"
    "Tamura corporation\n"
    "Techno Chips Co. Ltd\n"
    "Lanart Corporation\n"
    "Wellbean Co Inc\n"
    "ARM\n"
    "Dlog GmbH\n"
    "Logic Devices Inc\n"
    "Nokia Telecommunications oy\n"
    "Elecom Co Ltd\n"
    "Oxford Instruments\n"
    "Sanyo Technosound Co Ltd\n"
    "Bitran Corporation\n"
    "Sharp corporation\n"
    "Miroku Jyoho Service Co. Ltd\n"
    "Sharewave Inc\n"
    "Microgate Corporation\n"
    "3ware Inc\n"
    "Technotrend Systemtechnik GmbH\n"
    "Janz Computer AG\n"
    "Phase Metrics\n"
    "Alphi Technology Corp\n"
    "Condor Engineering Inc\n"
    "Blue Chip Technology Ltd\n"
    "Apptech Inc\n"
    "Eaton Corporation\n"
    "Iomega Corporation\n"
    "Yano Electric Co Ltd\n"
    "BARCO\n"
    "Compatible Systems Corporation\n"
    "Cocom A/S\n"
    "Studio Audio & Video Ltd\n"
    "Techsan Electronics Co Ltd\n"
    "Abocom Systems Inc\n"
    "Shark Multimedia Inc\n"
    "Graphics Microsystems Inc\n"
    "Media 100 Inc\n"
    "K.I. Technology Co Ltd\n"
    "Toshiba Engineering Corporation\n"
    "Phobos corporation\n"
    "Apex PC Solutions Inc\n"
    "Intresource Systems pte Ltd\n"
    "Janich & Klass Computertechnik GmbH\n"
    "Netboost Corporation\n"
    "Multimedia Bundle Inc\n"
    "ABB Robotics Products AB\n"
    "E-Tech Inc\n"
    "GVC Corporation\n"
    "Silicom Multimedia Systems Inc\n"
    "Dynamics Research Corporation\n"
    "Nest Inc\n"
    "Calculex Inc\n"
    "Telesoft Design Ltd\n"
    "Argosy research Inc\n"
    "NAC Incorporated\n"
    "Chip Express Corporation\n"
    "Intraserver Technology Inc\n"
    "Dallas Semiconductor\n"
    "Hauppauge Computer Works Inc\n"
    "Zydacron Inc\n"
    "Raytheion E-Systems\n"
    "Hayes Microcomputer Products Inc\n"
    "Coppercom Inc\n"
    "Sundance Technology Inc / IC Plus Corp\n"
    "Oce' - Technologies B.V.\n"
    "Ford Microelectronics Inc\n"
    "Brocade Communications Systems, Inc.\n"
    "Troika Networks, Inc.\n"
    "Kansai Electric Co. Ltd\n"
    "C-Media Electronics Inc\n"
    "Wildfire Communications\n"
    "Ad Lib Multimedia Inc\n"
    "NTT Advanced Technology Corp.\n"
    "Pentland Systems Ltd\n"
    "Aydin Corp\n"
    "Computer Peripherals International\n"
    "Micro Science Inc\n"
    "Advantech Co. Ltd\n"
    "Silicon Spice Inc\n"
    "Artx Inc\n"
    "CR-Systems A/S\n"
    "Meilhaus Electronic GmbH\n"
    "Ascor Inc\n"
    "Fundamental Software Inc\n"
    "Excalibur Systems Inc\n"
    "Oce' Printing Systems GmbH\n"
    "Lava Computer mfg Inc\n"
    "Aloka Co. Ltd\n"
    "Timedia Technology Co Ltd\n"
    "DSP Research Inc\n"
    "Abaco Systems, Inc.\n"
    "Elmic Systems Inc\n"
    "Matsushita Electric Works Ltd\n"
    "Goepel Electronic GmbH\n"
    "Salient Systems Corp\n"
    "Midas lab Inc\n"
    "Ikos Systems Inc\n"
    "VIA Technologies Inc.\n"
    "Addonics\n"
    "Microsoft Corporation\n"
    "Oxford Semiconductor Ltd\n"
    "Multiwave Innovation pte Ltd\n"
    "Convergenet Technologies Inc\n"
    "Kyushu electronics systems Inc\n"
    "Excel Switching Corp\n"
    "Apache Micro Peripherals Inc\n"
    "Zoom Telephonics Inc\n"
    "Digitan Systems Inc\n"
    "Fanuc Ltd\n"
    "Visiontech Ltd\n"
    "Psion Dacom plc\n"
    "Ads Technologies Inc\n"
    "Ygrec Systems Co Ltd\n"
    "Custom Technology Corp.\n"
    "Videoserver Connections\n"
    "Chelsio Communications Inc\n"
    "Storage Technology Corp.\n"
    "Better On-Line Solutions\n"
    "Edec Co Ltd\n"
    "Unex Technology Corp.\n"
    "Kingmax Technology Inc\n"
    "Radiolan\n"
    "Minton Optic Industry Co Ltd\n"
    "Pix stream Inc\n"
    "Vitec Multimedia\n"
    "Radicom Research Inc\n"
    "ITT Aerospace/Communications Division\n"
    "Gilat Satellite Networks\n"
    "Edimax Computer Co.\n"
    "Eltec Elektronik GmbH\n"
    "RTD Embedded Technologies, Inc.\n"
    "CIS Technology Inc\n"
    "Nissin Inc Co\n"
    "Atmel-dream\n"
    "Outsource Engineering & Mfg. Inc\n"
    "Stargate Solutions Inc\n"
    "Canon Research Center, America\n"
    "Amlogic Inc\n"
    "Tamarack Microelectronics Inc\n"
    "Jones Futurex Inc\n"
    "Lightwell Co Ltd - Zax Division\n"
    "ALGOL Corp.\n"
    "AGIE Ltd\n"
    "Phoenix Contact GmbH & Co.\n"
    "Unibrain S.A.\n"
    "TRW\n"
    "Logical DO Ltd\n"
    "Graphin Co Ltd\n"
    "AIM GmBH\n"
    "Alesis Studio Electronics\n"
    "TUT Systems Inc\n"
    "Adlink Technology\n"
    "Verint Systems Inc.\n"
    "Catalina Research Inc\n"
    "Samsung Electronics Co Ltd\n"
    "OLITEC\n"
    "Askey Computer Corp.\n"
    "Octave Communications Ind.\n"
    "SP3D Chip Design GmBH\n"
    "MYCOM Inc\n"
    "Altiga Networks\n"
    "Logic Plus Plus Inc\n"
    "Advanced Hardware Architectures\n"
    "Nuera Communications Inc\n"
    "Gigabyte Technology Co., Ltd\n"
    "DOOIN Electronics\n"
    "Escalate Networks Inc\n"
    "PRAIM SRL\n"
    "Cryptek\n"
    "Gallant Computer Inc\n"
    "Aashima Technology B.V.\n"
    "Baldor Electric Company\n"
    "DYNARC INC\n"
    "Avermedia Technologies Inc\n"
    "Micro-Star International Co., Ltd. [MSI]\n"
    "Fast Corporation\n"
    "Interactive Circuits & Systems Ltd\n"
    "GN NETTEST Telecom DIV.\n"
    "Designpro Inc.\n"
    "DIGICOM SPA\n"
    "AMBIT Microsystem Corp.\n"
    "Cleveland Motion Controls\n"
    "Aeroflex\n"
    "Parascan Technologies Ltd\n"
    "Ruby Tech Corp.\n"
    "Tachyon, INC.\n"
    "Williams Electronics Games, Inc.\n"
    "Multi Dimensional Consulting Inc\n"
    "Bay Networks\n"
    "Integrated Telecom Express Inc\n"
    "DAIKIN Industries, Ltd\n"
    "ZAPEX Technologies Inc\n"
    "Doug Carson & Associates\n"
    "PICAZO Communications\n"
    "MORTARA Instrument Inc\n"
    "Net Insight\n"
    "DIATREND Corporation\n"
    "TORAY Industries Inc\n"
    "FORMOSA Industrial Computing\n"
    "ABIT Computer Corp.\n"
    "AWARE, Inc.\n"
    "Interworks Computer Products\n"
    "Matsushita Graphic Communication Systems, Inc.\n"
    "NIHON UNISYS, Ltd.\n"
    "SCII Telecom\n"
    "BIOPAC Systems Inc\n"
    "ISYTEC - Integrierte Systemtechnik GmBH\n"
    "LABWAY Corporation\n"
    "Logic Corporation\n"
    "ERMA - Electronic GmBH\n"
    "L3 Communications Telemetry & Instrumentation\n"
    "MARQUETTE Medical Systems\n"
    "KYE Systems Corporation\n"
    "OPTO\n"
    "INNOMEDIALOGIC Inc.\n"
    "Tul Corporation / PowerColor\n"
    "DIGICOM Systems, Inc.\n"
    "OSI Plus Corporation\n"
    "Plant Equipment, Inc.\n"
    "Stone Microsystems PTY Ltd.\n"
    "ZEAL Corporation\n"
    "Time Logic Corporation\n"
    "MAKER Communications\n"
    "WINTOP Technology, Inc.\n"
    "TOKAI Communications Industry Co. Ltd\n"
    "JOYTECH Computer Co., Ltd.\n"
    "SMA Regelsysteme GmBH\n"
    "TEWS Technologies GmbH\n"
    "EMTEC CO., Ltd\n"
    "ANDOR Technology Ltd\n"
    "SEIKO Instruments Inc\n"
    "OVISLINK Corp.\n"
    "NEWTEK Inc\n"
    "Mapletree Networks Inc.\n"
    "LECTRON Co Ltd\n"
    "SOFTING GmBH\n"
    "Systembase Co Ltd\n"
    "Millennium Engineering Inc\n"
    "Maverick Networks\n"
    "Lite-On Technology Corporation\n"
    "XIONICS Document Technologies Inc\n"
    "INOVA Computers GmBH & Co KG\n"
    "MYTHOS Systems Inc\n"
    "FEATRON Technologies Corporation\n"
    "HIVERTEC Inc\n"
    "Advanced MOS Technology Inc\n"
    "Siemens Industry Software Inc.\n"
    "Novaweb Technologies Inc\n"
    "Time Space Radio AB\n"
    "CTI, Inc\n"
    "Guillemot Corporation\n"
    "BST Communication Technology Ltd\n"
    "Nextcom K.K.\n"
    "ENNOVATE Networks Inc\n"
    "XPEED Inc\n"
    "PHILIPS Business Electronics B.V.\n"
    "Creamware GmBH\n"
    "Quantum Data Corp.\n"
    "PROXIM Inc\n"
    "Techsoft Technology Co Ltd\n"
    "Cisco Aironet Wireless Communications\n"
    "INTERNIX Inc.\n"
    "SEMTECH Corporation\n"
    "Globespan Semiconductor Inc.\n"
    "CARDIO Control N.V.\n"
    "L3 Communications\n"
    "SPIDER Communications Inc.\n"
    "COMPAL Electronics Inc\n"
    "MYRICOM Inc.\n"
    "DTK Computer\n"
    "MEDIATEK Corp.\n"
    "IWASAKI Information Systems Co Ltd\n"
    "Automation Products AB\n"
    "Data Race Inc\n"
    "Modular Technology Holdings Ltd\n"
    "Turbocomm Tech. Inc.\n"
    "ODIN Telesystems Inc\n"
    "PE Logic Corp.\n"
    "Billionton Systems Inc\n"
    "NAKAYO Telecommunications Inc\n"
    "Universal Global Scientific Industrial Co.,Ltd\n"
    "Whistle Communications\n"
    "TEK Microsystems Inc.\n"
    "Ericsson Axe R & D\n"
    "Computer Hi-Tech Co Ltd\n"
    "Titan Electronics Inc\n"
    "CIRTECH (UK) Ltd\n"
    "Panacom Technology Corp\n"
    "Nitsuko Corporation\n"
    "Accusys Inc\n"
    "Hirakawa Hewtech Corp\n"
    "HOPF Elektronik GmBH\n"
    "Alliance Semiconductor Corporation\n"
    "National Aerospace Laboratories\n"
    "AFAVLAB Technology Inc\n"
    "Amplicon Liveline Ltd\n"
    "Boulder Design Labs Inc\n"
    "Applied Integration Corporation\n"
    "ASIC Communications Corp\n"
    "INVERTEX\n"
    "INFOLIBRIA\n"
    "AMTELCO\n"
    "Broadcom Inc. and subsidiaries\n"
    "Pixelfusion Ltd\n"
    "SHINING Technology Inc\n"
    "3CX\n"
    "RAYCER Inc\n"
    "GARNETS System CO Ltd\n"
    "Planex Communications, Inc\n"
    "SEIKO EPSON Corp\n"
    "Agilent Technologies\n"
    "DATAKINETICS Ltd\n"
    "MASPRO KENKOH Corp\n"
    "CARRY Computer ENG. CO Ltd\n"
    "CANON RESEACH CENTRE FRANCE\n"
    "Conexant Systems, Inc.\n"
    "MOBILITY Electronics\n"
    "BroadLogic\n"
    "TOKYO Electronic Industry CO Ltd\n"
    "SOPAC Ltd\n"
    "COYOTE Technologies LLC\n"
    "WOLF Technology Inc\n"
    "AUDIOCODES Inc\n"
    "AG COMMUNICATIONS\n"
    "WANDEL & GOLTERMANN\n"
    "TRANSAS MARINE (UK) Ltd\n"
    "Quadrics Ltd\n"
    "JAPAN Computer Industry Inc\n"
    "ARCHTEK TELECOM Corp\n"
    "TWINHEAD INTERNATIONAL Corp\n"
    "DELTA Electronics, Inc\n"
    "BANKSOFT CANADA Ltd\n"
    "MITSUBISHI ELECTRIC LOGISTICS SUPPORT Co Ltd\n"
    "KAWASAKI LSI USA Inc\n"
    "KAISER Electronics\n"
    "ITA INGENIEURBURO FUR TESTAUFGABEN GmbH\n"
    "CHAMELEON Systems Inc\n"
    "Motorola ?? / HTEC\n"
    "HONDA CONNECTORS/MHOTRONICS Inc\n"
    "FIRST INTERNATIONAL Computer Inc\n"
    "FORVUS RESEARCH Inc\n"
    "YAMASHITA Systems Corp\n"
    "KYOPAL CO Ltd\n"
    "WARPSPPED Inc\n"
    "C-PORT Corp\n"
    "INTEC GmbH\n"
    "BEHAVIOR TECH Computer Corp\n"
    "CENTILLIUM Technology Corp\n"
    "ROSUN Technologies Inc\n"
    "Raychem\n"
    "TFL LAN Inc\n"
    "Advent design\n"
    "MYSON Technology Inc\n"
    "ECHOTEK Corp\n"
    "Kontron\n"
    "TELEFON AKTIEBOLAGET LM Ericsson\n"
    "Globetek\n"
    "COMBOX Ltd\n"
    "DIGITAL AUDIO LABS Inc\n"
    "Fujitsu Computer Products Of America\n"
    "MATRIX Corp\n"
    "TOPIC SEMICONDUCTOR Corp\n"
    "CHAPLET System Inc\n"
    "BELL Corp\n"
    "MainPine Ltd\n"
    "MUSIC Semiconductors\n"
    "ENE Technology Inc\n"
    "IMPACT Technologies\n"
    "ISS, Inc\n"
    "SOLECTRON\n"
    "ACKSYS\n"
    "ON Semiconductor\n"
    "QUICKTURN DESIGN Systems\n"
    "FLYTECH Technology CO Ltd\n"
    "MACRAIGOR Systems LLC\n"
    "QUANTA Computer Inc\n"
    "MELEC Inc\n"
    "PHILIPS - CRYPTO\n"
    "ACQIS Technology Inc\n"
    "CHRYON Corp\n"
    "ECHELON Corp\n"
    "BALTIMORE\n"
    "ROAD Corp\n"
    "EVERGREEN Technologies Inc\n"
    "ACTIS Computer\n"
    "DATALEX COMMUNCATIONS\n"
    "ARALION Inc\n"
    "ATELIER INFORMATIQUES et ELECTRONIQUE ETUDES S.A.\n"
    "ONO SOKKI\n"
    "TERRATEC Electronic GmbH\n"
    "ANTAL Electronic\n"
    "FILANET Corp\n"
    "TECHWELL Inc\n"
    "MIPS Technologies, Inc.\n"
    "PROVIDEO MULTIMEDIA Co Ltd\n"
    "MACHONE Communications\n"
    "Concurrent Real-Time\n"
    "SILICON Laboratories\n"
    "DCM DATA Systems\n"
    "VISIONTEK\n"
    "IOI Technology Corp\n"
    "MITUTOYO Corp\n"
    "JET PROPULSION Laboratory\n"
    "INTERCONNECT Systems Solutions\n"
    "MAX Technologies Inc\n"
    "COMPUTEX Co Ltd\n"
    "VISUAL Technology Inc\n"
    "PAN INTERNATIONAL Industrial Corp\n"
    "SERVOTEST Ltd\n"
    "STRATABEAM Technology\n"
    "OPEN NETWORK Co Ltd\n"
    "SMART Electronic DEVELOPMENT GmBH\n"
    "RACAL AIRTECH Ltd\n"
    "CHICONY Electronics Co Ltd\n"
    "PROLINK Microsystems Corp\n"
    "GESYTEC GmBH\n"
    "PLDA\n"
    "MEDIASTAR Co Ltd\n"
    "CLEVO/KAPOK Computer\n"
    "SI LOGIC Ltd\n"
    "INNOMEDIA Inc\n"
    "PROTAC INTERNATIONAL Corp\n"
    "Cemax-Icon Inc\n"
    "Mac System Co Ltd\n"
    "LP Elektronik GmbH\n"
    "Perle Systems Ltd\n"
    "Terayon Communications Systems\n"
    "Viewgraphics Inc\n"
    "Symbol Technologies\n"
    "A-Trend Technology Co Ltd\n"
    "Yamakatsu Electronics Industry Co Ltd\n"
    "Biostar Microtech Int'l Corp\n"
    "Ardent Technologies Inc\n"
    "Jungsoft\n"
    "DDK Electronics Inc\n"
    "Palit Microsystems Inc.\n"
    "Avtec Systems\n"
    "2wire Inc\n"
    "Vidac Electronics GmbH\n"
    "Alpha-Top Corp\n"
    "Alfa Inc\n"
    "M-Systems Flash Disk Pioneers Ltd\n"
    "Teledyne Lecroy\n"
    "Contemporary Controls\n"
    "Otis Elevator Company\n"
    "Lattice - Vantis\n"
    "Fairchild Semiconductor\n"
    "Voltaire Advanced Data Security Ltd\n"
    "Viewcast COM\n"
    "HITT\n"
    "Dual Technology Corp\n"
    "Japan Elecronics Ind Inc\n"
    "Star Multimedia Corp\n"
    "Eurosoft (UK)\n"
    "Gemflex Networks\n"
    "Transition Networks\n"
    "PX Instruments Technology Ltd\n"
    "Primex Aerospace Co\n"
    "SEH Computertechnik GmbH\n"
    "Cytec Corp\n"
    "Inet Technologies Inc\n"
    "Uniwill Computer Corp\n"
    "Logitron\n"
    "Lancast Inc\n"
    "Konica Corp\n"
    "Solidum Systems Corp\n"
    "Atlantek Microsystems Pty Ltd\n"
    "Digalog Systems Inc\n"
    "Allied Data Technologies\n"
    "Hitachi Semiconductor & Devices Sales Co Ltd\n"
    "Point Multimedia Systems\n"
    "Lara Technology Inc\n"
    "Ditect Coop\n"
    "Hewlett Packard Enterprise\n"
    "ARN\n"
    "Syba Tech Ltd\n"
    "Bops Inc\n"
    "Netgame Ltd\n"
    "Diva Systems Corp\n"
    "Folsom Research Inc\n"
    "Memec Design Services\n"
    "Granite Microsystems\n"
    "Delta Electronics Inc\n"
    "General Instrument\n"
    "Faraday Technology Corp\n"
    "Stratus Computer Systems\n"
    "Ningbo Harrison Electronics Co Ltd\n"
    "A-Max Technology Co Ltd\n"
    "Galea Network Security\n"
    "Compumaster SRL\n"
    "Geocast Network Systems\n"
    "Catalyst Enterprises Inc\n"
    "Italtel\n"
    "X-Net OY\n"
    "Toyota Macs Inc\n"
    "Sunlight Ultrasound Technologies Ltd\n"
    "SSE Telecom Inc\n"
    "Shanghai Communications Technologies Center\n"
    "Moreton Bay\n"
    "Bluesteel Networks Inc\n"
    "North Atlantic Instruments\n"
    "VMware\n"
    "Amersham Pharmacia Biotech\n"
    "Zoltrix International Ltd\n"
    "Source Technology Inc\n"
    "Mosaid Technologies Inc\n"
    "Mellanox Technologies\n"
    "CCI/TRIAD\n"
    "Cimetrics Inc\n"
    "Texas Memory Systems Inc\n"
    "Sandisk Corp\n"
    "ADDI-DATA GmbH\n"
    "Maestro Digital Communications\n"
    "Impacct Technology Corp\n"
    "Portwell Inc\n"
    "Agilent Technologies\n"
    "DFI Inc\n"
    "Sola Electronics\n"
    "High Tech Computer Corp (HTC)\n"
    "BVM Ltd\n"
    "Quantel\n"
    "Newer Technology Inc\n"
    "Taiwan Mycomp Co Ltd\n"
    "EVSX Inc\n"
    "Procomp Informatics Ltd\n"
    "Technical University of Budapest\n"
    "Tateyama System Laboratory Co Ltd\n"
    "Penta Media Co Ltd\n"
    "Serome Technology Inc\n"
    "Bitboys OY\n"
    "AG Electronics Ltd\n"
    "Hotrail Inc\n"
    "Dreamtech Co Ltd\n"
    "Genrad Inc\n"
    "Hilscher Gesellschaft f\xfcr Systemautomation mbH\n"
    "Infineon Technologies AG\n"
    "FIC (First International Computer Inc)\n"
    "NDS Technologies Israel Ltd\n"
    "Iwill Corp\n"
    "Tatung Co\n"
    "Entridia Corp\n"
    "Rockwell-Collins Inc\n"
    "Cybernetics Technology Co Ltd\n"
    "Super Micro Computer Inc\n"
    "Cyberfirm Inc\n"
    "Applied Computing Systems Inc\n"
    "Litronic Inc\n"
    "Sigmatel Inc\n"
    "Malleable Technologies Inc\n"
    "Infinilink Corp\n"
    "Cacheflow Inc\n"
    "Voice Technologies Group Inc\n"
    "Quicknet Technologies Inc\n"
    "Networth Technologies Inc\n"
    "VSN Systemen BV\n"
    "Valley technologies Inc\n"
    "Agere Inc\n"
    "Get Engineering Corp\n"
    "National Datacomm Corp\n"
    "Pacific Digital Corp\n"
    "Tokyo Denshi Sekei K.K.\n"
    "DResearch Digital Media Systems GmbH\n"
    "Beckhoff GmbH\n"
    "Macrolink Inc\n"
    "In Win Development Inc\n"
    "Intelligent Paradigm Inc\n"
    "B-Tree Systems Inc\n"
    "Times N Systems Inc\n"
    "Diagnostic Instruments Inc\n"
    "Digitmedia Corp\n"
    "Valuesoft\n"
    "Power Micro Research\n"
    "Extreme Packet Device Inc\n"
    "Banctec\n"
    "Koga Electronics Co\n"
    "Zenith Electronics Corp\n"
    "J.P. Axzam Corp\n"
    "Zilog Inc\n"
    "Techsan Electronics Co Ltd\n"
    "N-CUBED.NET\n"
    "Kinpo Electronics Inc\n"
    "Fastpoint Technologies Inc\n"
    "Northrop Grumman - Canada Ltd\n"
    "Tenta Technology\n"
    "Prosys-tec Inc\n"
    "Nokia Wireless Communications\n"
    "Central System Research Co Ltd\n"
    "Pairgain Technologies\n"
    "Europop AG\n"
    "Lava Semiconductor Manufacturing Inc\n"
    "Automated Wagering International\n"
    "Scimetric Instruments Inc\n"
    "Telesynergy Research Inc.\n"
    "Stone Ridge Technology\n"
    "FarSite Communications Ltd\n"
    "Rioworks\n"
    "Lynx Studio Technology, Inc.\n"
    "TDK Semiconductor Corp.\n"
    "Kongsberg Spacetec AS\n"
    "Packard Bell B.V.\n"
    "Standard Microsystems Corp [SMC]\n"
    "Smart Link Ltd.\n"
    "MKNet Corp.\n"
    "Bitland(ShenZhen) Information Technology Co., Ltd.\n"
    "Cavium QLogic\n"
    "Epix Inc\n"
    "Gidel Ltd.\n"
    "Hsing Tech. Enterprise Co., Ltd.\n"
    "Linux Media Labs, LLC\n"
    "Worldspace Corp.\n"
    "EDAX Inc\n"
    "Actiontec Electronics Inc\n"
    "Broadcom Corporation\n"
    "B&R Industrial Automation GmbH\n"
    "NetEffect\n"
    "Tokyo Electron Device Ltd.\n"
    "ZyDAS Technology Corp.\n"
    "Samsung Electro-Mechanics Co., Ltd.\n"
    "ONNTO Corp.\n"
    "Hercules\n"
    "XFX Pine Group Inc.\n"
    "CastleNet Technology Inc.\n"
    "Utimaco IS GmbH\n"
    "Qualcomm Atheros\n"
    "EPoX Computer Co., Ltd.\n"
    "Netcell Corporation\n"
    "Club-3D VB (Wrong ID)\n"
    "Tekram Technology Co.,Ltd.\n"
    "Global Sun Technology Inc\n"
    "SafeNet Inc\n"
    "SparkLAN Communications, Inc.\n"
    "Aspex Semiconductor Ltd\n"
    "Sonnet Technologies, Inc.\n"
    "Creatix Polymedia GmbH\n"
    "Synopsys, Inc.\n"
    "Micrel-Kendin\n"
    "Octasic Inc.\n"
    "EONIC B.V. The Netherlands\n"
    "CENATEK Inc\n"
    "Advantech Co. Ltd\n"
    "Roland Corp.\n"
    "Acromag, Inc.\n"
    "Advantech Co., Ltd.\n"
    "PIKA Technologies Inc.\n"
    "Marvin Test Solutions\n"
    "European Space Agency\n"
    "Intellon Corp.\n"
    "U.S. Robotics\n"
    "Sycron N. V.\n"
    "ETAS GmbH\n"
    "Jetway Information Co., Ltd.\n"
    "Vweb Corp\n"
    "VideoTele.com, Inc.\n"
    "Internet Machines Corporation (IMC)\n"
    "Digital First, Inc.\n"
    "NetOctave\n"
    "YottaYotta Inc.\n"
    "EZChip Technologies\n"
    "Vitesse Semiconductor\n"
    "Accelerated Encryption\n"
    "Sparkle Computer Co., Ltd.\n"
    "Fujitsu Technology Solutions\n"
    "Aten International Co. Ltd.\n"
    "Linksys\n"
    "Altima (nee Broadcom)\n"
    "Peppercon AG\n"
    "ViXS Systems, Inc.\n"
    "RLX Technologies\n"
    "PC Partner Limited / Sapphire Technology\n"
    "WellX Telecom SA\n"
    "AudioScience Inc\n"
    "Sanera Systems, Inc.\n"
    "TEDIA spol. s r. o.\n"
    "Pickering Interfaces Ltd\n"
    "InnoVISION Multimedia Ltd.\n"
    "General Electric\n"
    "Cavium, Inc.\n"
    "Hightech Information System Ltd.\n"
    "Ennyah Technologies Corp.\n"
    "Research Centre Juelich\n"
    "Intersil Techwell\n"
    "Belkin\n"
    "id Quantique\n"
    "Data Patterns\n"
    "Genesys Logic, Inc\n"
    "Lenovo\n"
    "Phillips Components\n"
    "Hightech Information System Ltd.\n"
    "Hawking Technologies\n"
    "Indra Networks, Inc.\n"
    "Wistron Corp.\n"
    "Newisys, Inc.\n"
    "Protogate, Inc.\n"
    "Qualcomm Technologies, Inc\n"
    "NetChip Technology, Inc\n"
    "Cadence Design Systems, Inc.\n"
    "Z-Com, Inc.\n"
    "Areca Technology Corp.\n"
    "Exar Corp.\n"
    "Cray Inc\n"
    "KWorld Computer Co. Ltd.\n"
    "Dini Group\n"
    "Sectra AB\n"
    "MaxLinear\n"
    "Connect Components Ltd\n"
    "Albatron Corp.\n"
    "RDC Semiconductor, Inc.\n"
    "Topdek Semiconductor Inc.\n"
    "Gemtek Technology Co., Ltd\n"
    "IOGEAR, Inc.\n"
    "InProComm Inc.\n"
    "Benq Corporation\n"
    "Qualcore Logic Inc.\n"
    "ProdaSafe GmbH\n"
    "Ralink corp. (wrong ID)\n"
    "Euresys S.A.\n"
    "Lumanate, Inc.\n"
    "IEI Integration Corp\n"
    "Ambient Technologies Inc\n"
    "Ralink corp.\n"
    "Devolo AG\n"
    "InfiniCon Systems Inc.\n"
    "Twinhan Technology Co. Ltd\n"
    "SiteCom Europe BV\n"
    "Raza Microelectronics, Inc.\n"
    "Broadcom\n"
    "Credence Systems Corporation\n"
    "MikroM GmbH\n"
    "Alcatel-Lucent\n"
    "ASRock Incorporation\n"
    "Thales Computers\n"
    "Advantest Corporation\n"
    "Microtune, Inc.\n"
    "Anritsu Corp.\n"
    "SMSC Automotive Infotainment System Group\n"
    "LG Electronics, Inc.\n"
    "Compro Technology, Inc.\n"
    "Wistron NeWeb Corp.\n"
    "SilverBack\n"
    "Topspin Communications\n"
    "Humusoft, s.r.o.\n"
    "WiNRADiO Communications\n"
    "L-3 Communications\n"
    "ZyXEL Communications Corporation\n"
    "Avvida Systems Inc.\n"
    "Varisys Ltd\n"
    "Ample Communications, Inc\n"
    "Egenera, Inc.\n"
    "KNC One\n"
    "B&B Electronics Manufacturing Company, Inc.\n"
    "AMtek\n"
    "Astute Networks Inc.\n"
    "Stretch Inc.\n"
    "AT&T\n"
    "DViCO Corporation\n"
    "Ammasso\n"
    "GeCube Technologies, Inc.\n"
    "Micronas Semiconductor Holding AG\n"
    "Cray Inc\n"
    "ARVOO Engineering BV\n"
    "XGI Technology Inc. (eXtreme Graphics Innovation)\n"
    "Sitecom Europe BV (Wrong ID)\n"
    "Celestica\n"
    "Dialogue Technology Corp.\n"
    "Artimi Inc\n"
    "LeWiz Communications\n"
    "MPL AG\n"
    "Advance Multimedia Internet Technology, Inc.\n"
    "Cesnet, z.s.p.o.\n"
    "Chenming Mold Ind. Corp.\n"
    "Spectrum GmbH\n"
    "Napatech A/S\n"
    "NextIO\n"
    "Commtech, Inc.\n"
    "Resilience Corporation\n"
    "Hangzhou Silan Microelectronics Co., Ltd.\n"
    "Micronas USA, Inc.\n"
    "Renesas Electronics Corp.\n"
    "Soltek Computer Inc.\n"
    "Sangoma Technologies Corp.\n"
    "AMD Solarflare\n"
    "BiTMICRO Networks Inc.\n"
    "TransDimension\n"
    "Option N.V.\n"
    "DiBcom\n"
    "MAXIM Integrated Products\n"
    "New H3C Technologies Co., Ltd.\n"
    "AHA Products Group\n"
    "ClearSpeed Technology plc\n"
    "MERA\n"
    "C-guys, Inc.\n"
    "Alpha Networks Inc.\n"
    "DapTechnology B.V.\n"
    "One Stop Systems, Inc.\n"
    "Freescale Semiconductor Inc\n"
    "Faster Technology, LLC.\n"
    "PA Semi, Inc\n"
    "Orad Hi-Tec Systems\n"
    "Qualcomm Atheros\n"
    "Sensory Networks Inc.\n"
    "Club-3D BV\n"
    "PNY\n"
    "AGEIA Technologies, Inc.\n"
    "Star Electronics GmbH & Co. KG\n"
    "TRENDnet\n"
    "Parsec\n"
    "JMicron Technology Corp.\n"
    "Distant Early Warning Communications Inc\n"
    "Phison Electronics Corporation\n"
    "Montilio Inc.\n"
    "Nallatech Ltd.\n"
    "Innominate Security Technologies AG\n"
    "Toyou Feiji Electronics Co., Ltd.\n"
    "A-Logics\n"
    "Pulse-LINK, Inc.\n"
    "Xsigo Systems\n"
    "Auvitek\n"
    "Emulex Corporation\n"
    "Owl Cyber Defense Solutions\n"
    "DAQDATA GmbH\n"
    "Kasten Chase Applied Research\n"
    "Progeny Systems Corporation\n"
    "ZyXEL Communications Corp.\n"
    "Exegy Inc.\n"
    "Motorola Expedience\n"
    "Quixant Limited\n"
    "ZOTAC International (MCO) Ltd.\n"
    "Pico Computing\n"
    "Vector Informatik GmbH\n"
    "DDRdrive LLC\n"
    "Huawei Technologies Co., Ltd.\n"
    "NET (Network Equipment Technologies)\n"
    "Netronome Systems, Inc.\n"
    "BFG Tech\n"
    "ESI Audiotechnik GmbH\n"
    "Eclipse Electronic Systems, Inc.\n"
    "ASPEED Technology, Inc.\n"
    "deltaww\n"
    "Kvaser AB\n"
    "Sierra semiconductor\n"
    "SEAKR Engineering\n"
    "DekTec Digital Video B.V.\n"
    "Force10 Networks, Inc.\n"
    "GFaI e.V.\n"
    "3Leaf Systems, Inc.\n"
    "Ambric Inc.\n"
    "Fortinet, Inc.\n"
    "Ascom AG\n"
    "Lantiq\n"
    "Quanta Microsystems, Inc\n"
    "AzureWave\n"
    "Micro-Research Finland Oy\n"
    "Tilera Corp.\n"
    "SLAC National Accelerator Lab TID-ID\n"
    "Hectronic AB\n"
    "Rohde & Schwarz DVS GmbH\n"
    "Rivet Networks\n"
    "Highly Reliable Systems\n"
    "Razer USA Ltd.\n"
    "Celoxica\n"
    "Aprius Inc.\n"
    "System TALKS Inc.\n"
    "VirtenSys Limited\n"
    "XenSource, Inc.\n"
    "Violin Memory, Inc\n"
    "Wavesat\n"
    "Lightfleet Corporation\n"
    "Virident Systems Inc.\n"
    "Commex Technologies\n"
    "Duagon AG\n"
    "StarBridge, Inc.\n"
    "Verigy Pte. Ltd.\n"
    "DRS Technologies\n"
    "Ciprico, Inc.\n"
    "Schweitzer Engineering Laboratories\n"
    "Silver Creations AG\n"
    "Global Velocity, Inc.\n"
    "Distributed Management Task Force, Inc. (DMTF)\n"
    "CalDigit, Inc.\n"
    "Parallels, Inc.\n"
    "Espia Srl\n"
    "Global Unichip Corp.\n"
    "Aeroflex Gaisler\n"
    "Point of View BV\n"
    "Spectracom Corporation\n"
    "Spin Master Ltd.\n"
    "Google, Inc.\n"
    "SANBlaze Technology, Inc.\n"
    "First Wise Media GmbH\n"
    "Basler AG\n"
    "Wilocity Ltd.\n"
    "Alcor Micro\n"
    "Wolfson Microelectronics\n"
    "SanDisk\n"
    "Caustic Graphics Inc.\n"
    "Red Hat, Inc.\n"
    "Netezza Corp.\n"
    "J & W Electronics Co., Ltd.\n"
    "Montage Technology Co., Ltd.\n"
    "Magnum Semiconductor, Inc,\n"
    "Tria Technologies GmbH\n"
    "Pegatron\n"
    "Jaton Corp\n"
    "K&F Computing Research Co.\n"
    "Corsair\n"
    "ASMedia Technology Inc.\n"
    "Netcope Technologies, a.s.\n"
    "Opal-RT Technologies Inc.\n"
    "Red Hat, Inc.\n"
    "Signal Processing Devices Sweden AB\n"
    "sTec, Inc.\n"
    "Westar Display Technologies\n"
    "Teradata Corp.\n"
    "Schooner Information Technology, Inc.\n"
    "Numascale AS\n"
    "Marvell Technology Group Ltd.\n"
    "GALAX\n"
    "NetUP Inc.\n"
    "Achronix Semiconductor Corporation\n"
    "STAR-Dundee Ltd.\n"
    "Byd Precision Manufacture Co.,Ltd\n"
    "DELTACAST\n"
    "Etron Technology, Inc.\n"
    "Fresco Logic\n"
    "OpenVox Communication Co. Ltd.\n"
    "Absolute Analysis\n"
    "OCZ Technology Group, Inc.\n"
    "Signatec / Dynamic Signals Corp\n"
    "Western Digital\n"
    "XAVi Technologies Corp.\n"
    "QNAP Systems, Inc.\n"
    "ReFLEX CES\n"
    "SimpliVity Corporation\n"
    "Seagate Technology PLC\n"
    "Bluecherry\n"
    "Quantenna Communications, Inc.\n"
    "Maxeler Technologies Ltd.\n"
    "Innodisk Corporation\n"
    "Apacer Technology\n"
    "NEC Corporation\n"
    "Astronics Corporation\n"
    "IEIT SYSTEMS Co., Ltd\n"
    "IXXAT Automation GmbH\n"
    "Lantiq\n"
    "VTI Instruments Corporation\n"
    "Greenliant\n"
    "Duagon AG\n"
    "EeeTOP\n"
    "WCH (Nanjing Qinheng Microelectronics Co., Ltd.)\n"
    "CSP, Inc.\n"
    "LaCie\n"
    "Symphony\n"
    "SoftLab-NSK\n"
    "Lite-On IT Corp. / Plextor\n"
    "Silicom Denmark\n"
    "Highland Technology, Inc.\n"
    "Daktronics, Inc\n"
    "Annapurna Labs Ltd.\n"
    "Accensus, LLC\n"
    "Enmotus Inc\n"
    "TECHWAY\n"
    "HGST, Inc.\n"
    "SK hynix\n"
    "Beijing Memblaze Technology Co. Ltd.\n"
    "Science and Research Centre of Computer Technology (JSC \"NICEVT\")\n"
    "PreSonus Audio Electronics Inc.\n"
    "OWC\n"
    "TTTech Computertechnik AG\n"
    "Elektrobit Austria GmbH\n"
    "TSF5 Corporation\n"
    "Mobiveil, Inc.\n"
    "Shannon Systems\n"
    "Collion UG & Co.KG\n"
    "Focusrite Audio Engineering Ltd\n"
    "Dawning Information Industry Co., Ltd.\n"
    "ADATA Technology Co., Ltd.\n"
    "Shenzhen Unionmemory Information System Ltd.\n"
    "Embedded Intelligence, Inc.\n"
    "Radian Memory Systems Inc.\n"
    "Zoom Corporation\n"
    "Seskion GmbH\n"
    "Nanjing Magewell Electronics Co., Ltd.\n"
    "secunet Security Networks AG\n"
    "Exablaze\n"
    "Akitio\n"
    "ZTE Corp.\n"
    "Subspace Dynamics\n"
    "Corsair Memory, Inc\n"
    "Mangstor\n"
    "Pure Storage\n"
    "AIstone Global Limited\n"
    "Amazon.com, Inc.\n"
    "Zhaoxin\n"
    "RME\n"
    "Barefoot Networks, Inc.\n"
    "CNEX Labs\n"
    "Allo\n"
    "Baidu Technology\n"
    "Kalray Inc.\n"
    "KAYA Instruments\n"
    "NovaSparks\n"
    "Baikal Electronics\n"
    "Techman Electronics (Changshu) Co., Ltd.\n"
    "DPT\n"
    "Lenovo\n"
    "Diamanti, Inc.\n"
    "Fantasia Trading LLC\n"
    "Technobox, Inc.\n"
    "Nebbiolo Technologies\n"
    "StorArt Technology Co., Ltd\n"
    "Imagine Communications Corp.\n"
    "Renesas Electronics Corp.\n"
    "Aquantia Corp.\n"
    "Atomic Rules LLC\n"
    "Xiaomi\n"
    "DERA Storage\n"
    "Transcend Information, Inc.\n"
    "Aerotech, Inc.\n"
    "NETINT Technologies Inc.\n"
    "Rockchip Electronics Co., Ltd\n"
    "YEESTOR Microelectronics Co., Ltd\n"
    "Exegy\n"
    "Abaco Systems Inc.\n"
    "YADRO\n"
    "Chengdu Haiguang IC Design Co., Ltd.\n"
    "Graphcore Ltd\n"
    "Shenzhen Longsys Electronics Co., Ltd.\n"
    "Meta Platforms, Inc.\n"
    "Teko Telecom S.r.l.\n"
    "Sapphire Technology Limited\n"
    "Habana Labs Ltd.\n"
    "Corigine, Inc.\n"
    "Fungible\n"
    "ATP Electronics, Inc.\n"
    "Unisoc (Shanghai) Technologies Co., Ltd.\n"
    "Phytium Technology Co., Ltd.\n"
    "NGD Systems, Inc.\n"
    "INNOGRIT Corporation\n"
    "Guizhou Huaxintong Semiconductor Technology Co., Ltd\n"
    "Alco Digital Devices Limited\n"
    "FADU Inc.\n"
    "Liqid Inc.\n"
    "Beijing Sinead Technology Co., Ltd.\n"
    "Sage Microelectronics Corp.\n"
    "Swissbit AG\n"
    "Manli Technology Group Limited\n"
    "AMD Pensando Systems\n"
    "Thorlabs\n"
    "Groq\n"
    "Tekram Technology Co.,Ltd.\n"
    "Raspberry Pi Ltd\n"
    "Eideticom, Inc\n"
    "Alibaba (China) Co., Ltd.\n"
    "Biwin Storage Technology Co., Ltd.\n"
    "Ampere Computing, LLC\n"
    "Ethernity Networks\n"
    "Shenzhen TIGO Semiconductor\n"
    "opencpi.org\n"
    "V&G Information System Co.,Ltd\n"
    "Astera Labs, Inc.\n"
    "JSC NT-COM\n"
    "Shenzhen Decenta Technology Co.,LTD\n"
    "SambaNova Systems, Inc\n"
    "KIOXIA Corporation\n"
    "Arnold & Richter Cine Technik GmbH & Co. Betriebs KG\n"
    "Beijing GuangRunTong Technology Development Co.,Ltd\n"
    "Squirrels Research Labs\n"
    "Fujitsu Client Computing Limited\n"
    "Sophgo\n"
    "SORD CORPORATION\n"
    "Shanghai Enflame Technology Co. Ltd\n"
    "Blaize, Inc\n"
    "MEDION AG\n"
    "Cactus Technologies Limited\n"
    "DapuStor Corporation\n"
    "Burlywood, Inc\n"
    "Shanghai Iluvatar CoreX Semiconductor Co., Ltd.\n"
    "MaxLinear Inc\n"
    "Valve Software\n"
    "Aumovio\n"
    "Yangtze Memory Technologies Co.,Ltd\n"
    "MAXIO Technology (Hangzhou) Ltd.\n"
    "GSI Technology\n"
    "IP3 Tech (HK) Limited\n"
    "Tenstorrent Inc\n"
    "Beijing Panyi Technology Co., Ltd\n"
    "Oxford Nanopore Technologies\n"
    "ASR Microelectronics\n"
    "Hailo Technologies Ltd.\n"
    "Untether AI\n"
    "Jiangsu Xinsheng Intelligent Technology Co., Ltd\n"
    "Axiado Corp.\n"
    "Xsight Labs Ltd.\n"
    "Dataland\n"
    "Brainchip Inc\n"
    "Pliops\n"
    "Jiangsu Huacun Elec. Tech. Co., Ltd.\n"
    "Ramaxel Technology(Shenzhen) Limited\n"
    "Huaqin Technology Co.Ltd\n"
    "HEITEC AG\n"
    "ID Quantique SA\n"
    "Beijing Bytedance Network Technology Co., Ltd.\n"
    "Calian SED\n"
    "Solid State Storage Technology Corporation\n"
    "Drut Technologies Inc.\n"
    "Lynxi Technologies Co., Ltd.\n"
    "Tencent Technology (Shenzhen) Company Limited\n"
    "Intelliprop, Inc\n"
    "Hefei DATANG Storage Technology Co.,LTD.\n"
    "Quectel Wireless Solutions Co., Ltd.\n"
    "XFX Limited\n"
    "Shenzhen Electrical Appliances CO.\n"
    "VeriSilicon Inc\n"
    "Quantum Nebula Microelectronics Technology Co.,Ltd.\n"
    "Wuxi Stars Microsystem Technology Co., Ltd\n"
    "Senscomm Semiconductor, Inc\n"
    "EMERGETECH Company Ltd.\n"
    "Vastai Technologies\n"
    "Beijing Fantasy Technology Co., Ltd.\n"
    "Wingtech Group(HongKong)Limited\n"
    "Lightmatter\n"
    "Hosin Global Electronics\n"
    "FuriosaAI, Inc.\n"
    "Yeston\n"
    "Moore Threads Technology Co.,Ltd\n"
    "Digiteq Automotive\n"
    "Myrtle.ai\n"
    "Suzhou Kuhan Information Technologies\n"
    "PETAIO INC\n"
    "SUSE LLC\n"
    "Viscore Technologies Ltd\n"
    "XDX Computing Technology Ltd.\n"
    "GrAI Matter Labs\n"
    "Shenzhen Gunnir Technology Development Co., Ltd\n"
    "Flexxon Pte Ltd\n"
    "Rebellions Inc.\n"
    "Beijing Dayu Technology\n"
    "Shenzhen Shichuangyi Electronics Co., Ltd\n"
    "Motorcomm Microelectronics.\n"
    "DeGirum Corp.\n"
    "NebulaMatrix Technology\n"
    "XConn Technologies\n"
    "Zettastone Technology\n"
    "c-payne GmbH\n"
    "Sophgo Technologies Inc.\n"
    "xFusion Digital Technologies Co., Ltd.\n"
    "AzurEngine Technologies\n"
    "China Mobile (Hangzhou) Information Technology Co.Ltd.\n"
    "Nextorage\n"
    "Wuhan YuXin Semiconductor Co., Ltd.\n"
    "3SNIC Ltd\n"
    "Netac Technology Co.,Ltd\n"
    "VVDN Technologies Private Limited\n"
    "YUSUR Technology\n"
    "NeuReality LTD\n"
    "Axera Semiconductor Co., Ltd\n"
    "MangoBoost Inc.\n"
    "SAPEON Inc.\n"
    "Accelecom\n"
    "Yunsilicon Technology\n"
    "CIX Technology Group Co., Ltd.\n"
    "Shenzhen Quanxing Tech Co., Ltd.\n"
    "Efinix, Inc.\n"
    "d-Matrix\n"
    "Exascend,INC.\n"
    "Quside Technologies\n"
    "Shenzhen Techwinsemi Technology Co., Ltd.\n"
    "Axelera AI\n"
    "Shandong SinoChip Semiconductors Co., Ltd\n"
    "Hexaflake (Shanghai) Information Technology Co., Ltd.\n"
    "Unifabrix Ltd.\n"
    "ICube Corporation Limited\n"
    "Shenzhen Enrigin Technology Co., Ltd.\n"
    "Ascom (Finland) Oy\n"
    "QLogic, Corp.\n"
    "Emerson\n"
    "Tehuti Networks Ltd.\n"
    "Varex Imaging Deutschland AG\n"
    "StreamLabs\n"
    "Cognio Inc.\n"
    "SUNIX Co., Ltd.\n"
    "Wuqi Microelectronics Co., Ltd.\n"
    "Kratos Defense & Security Solutions, Inc.\n"
    "Allwinmeta Co., Ltd.\n"
    "Beijing ESWIN Computing Technology Co., Ltd.\n"
    "HippStor Technology\n"
    "MemryX\n"
    "Linkdata\n"
    "DEEPX Co., Ltd.\n"
    "Beijing Gengtu Technology Co.Ltd\n"
    "Inagile Electronic Technology Co., LTD\n"
    "DENSO Corporation\n"
    "Smart Link Ltd.\n"
    "Temporal Research Ltd\n"
    "Smart Link Ltd.\n"
    "Smart Link Ltd.\n"
    "SpacemiT\n"
    "CAEN S.p.A.\n"
    "Netforward Microelectronics Co., Ltd.\n"
    "XTX Markets Technologies Ltd.\n"
    "Xi'an UniIC Semiconductors Co., Ltd\n"
    "Shenzhen Jiahua Zhongli Technology Co., LTD.\n"
    "GXMICRO Technology (Shanghai) Co., Ltd.\n"
    "Beijing SpaceControl Technology Co.Ltd\n"
    "Frontgrade Gaisler AB\n"
    "Lime Microsystems Ltd.\n"
    "Zhejiang VMing Semiconductor Co., Ltd.\n"
    "Shanghai Zijing Xinjie Intelligent Technology Co., Ltd.\n"
    "SDTECH\n"
    "Unis Flash Memory\n"
    "Hubei Yangtze Mason Semiconductor Technology Co., Ltd.\n"
    "GigaIO Networks, Inc.\n"
    "OpenAI\n"
    "HRDT\n"
    "MICIUS Laboratory\n"
    "Shenzhen Wodposit Electronics Co., Ltd.\n"
    "Kaitian Information Technology Co., Ltd.\n"
    "Rolling Wireless S.a.r.l.\n"
    "BitIntelligence Technology\n"
    "Mobilint, Inc.\n"
    "Etched, Inc.\n"
    "XCENA, Inc.\n"
    "EEVengers Inc.\n"
    "Rayson HI-TECH(SZ) Co., Ltd.\n"
    "LDA Technologies Ltd.\n"
    "Shanghai StarFive Technology Co., Ltd.\n"
    "Hangzhou Hikstorage Technology Co., Ltd.\n"
    "Quantum Machines\n"
    "Xinsheng Technology Co., Ltd.\n"
    "ExpectedIT GmbH\n"
    "Suzhou Yige Technology Co., Ltd.\n"
    "Telin Semiconductor (Wuhan) Co., Ltd.\n"
    "Awide Labs LTD.\n"
    "EHTech (Beijing) Co. Ltd.\n"
    "Sharetronic Data Technology Co., Ltd.\n"
    "CECloud Computing Technology Co., Ltd.\n"
    "Elix Systems SA\n"
    "TOPSSD\n"
    "TRENDnet\n"
    "Shenzhen Zhishi Network Technology Co., Ltd.\n"
    "Shenzhen Silicon Dynamic Networks Co., Ltd.\n"
    "Shenzhen Kimviking Semiconductor Co., Ltd.\n"
    "Shanghai Timar Integrated Circuit Co., LTD\n"
    "ZCHL Technology Co., Ltd\n"
    "HuiLink Technologies (Xiamen) Co., Ltd.\n"
    "EigenQ, Inc.\n"
    "ZyDAS Technology Corp.\n"
    "Shanghai Warpdrive Technology Co., Ltd\n"
    "Hunan Goke Microelectronics Co., Ltd\n"
    "21st Century Computer Corp.\n"
    "Flex-Logix Technologies\n"
    "Missing Link Electronics, Inc.\n"
    "Colorgraphic Communications Corp.\n"
    "Bruker AXS Inc.\n"
    "Racore\n"
    "Graphics Technology (HK) Co., Ltd.\n"
    "Kingston Technology Company, Inc.\n"
    "Xantel Corporation\n"
    "Chaintech Computer Co. Ltd\n"
    "AVID Technology Inc.\n"
    "Emdoor Digital Technology Co., Ltd\n"
    "Connectix Virtual PC\n"
    "3D Vision(???)\n"
    "Video Transcode Controller\n"
    "ROPEX Industrie-Elektronik GmbH\n"
    "Maginfra Co., LTD\n"
    "Hansol Electronics Inc.\n"
    "Luxvisions Innovation Technology Ltd.\n"
    "Dynabook Inc.\n"
    "Satelco Ingenieria S.A.\n"
    "AUDIOTRAK\n"
    "Post Impression Systems.\n"
    "Zonet\n"
    "Shenzhen EMEET Technology Co., Ltd.\n"
    "Hint Corp\n"
    "Quantum Designs (H.K.) Inc\n"
    "Bihl+Wiedemann GmbH\n"
    "Arista Networks, Inc.\n"
    "Ice Lake-LP PCI Express Root Port #3\n"
    "ARCOM Control Systems Ltd\n"
    "DeepCool\n"
    "HighSecLabs, Ltd.\n"
    "ITD Firm ltd.\n"
    "EVGA Corporation\n"
    "4Links\n"
    "Lenovo (wrong ID)\n"
    "3DLabs\n"
    "Sinead Tech Co., Ltd\n"
    "Avance Logic Inc.\n"
    "Addtron Technology Co, Inc.\n"
    "NetXen Incorporated\n"
    "Digital Equipment Corp\n"
    "Alpha Data\n"
    "AIMOTIVE Kft.\n"
    "ONA Electroerosion\n"
    "Auzentech, Inc.\n"
    "Aladdin Knowledge Systems\n"
    "Universall Answer Generators\n"
    "DVBSky\n"
    "Tata Power Strategic Electronics Division\n"
    "WCH.CN\n"
    "Cornelis Networks\n"
    "Internext Compression Inc\n"
    "Bridgeport machines\n"
    "Cogetec Informatique Inc\n"
    "Baldor Electric Company\n"
    "Budker Institute of Nuclear Physics\n"
    "TXIC\n"
    "Umax Computer Corp\n"
    "Hercules Computer Technology Inc\n"
    "RedCreek Communications Inc\n"
    "Growth Networks\n"
    "ACCES I/O Products, Inc.\n"
    "Axil Computer Inc\n"
    "NetVin\n"
    "Buslogic Inc.\n"
    "KonteX Inc.\n"
    "LUNG HWA Electronics\n"
    "Liquid-Markets GmbH\n"
    "LR-LINK\n"
    "SBS Technologies\n"
    "Lisuan Technology Co., Ltd.\n"
    "Seanix Technology Inc\n"
    "MediaQ Inc.\n"
    "Microtechnica Co Ltd\n"
    "Balluff MV GmbH\n"
    "ILC Data Device Corp\n"
    "NieL TechSolution\n"
    "Nutanix, Inc.\n"
    "University of Toronto\n"
    "GemTek Technology Corporation\n"
    "Voyetra Technologies\n"
    "TerraTec Electronic GmbH\n"
    "System-on-Chip Engineering S.L.\n"
    "S S Technologies\n"
    "Qualcomm Inc\n"
    "Ensoniq (Old)\n"
    "Animation Technologies Inc.\n"
    "Alliance Semiconductor Corp.\n"
    "S3 Graphics Ltd.\n"
    "AuzenTech, Inc.\n"
    "Teralogic Inc\n"
    "TBS Technologies\n"
    "SCANLAB AG\n"
    "Technische Universitaet Berlin\n"
    "GoTView\n"
    "Cnet Technologies, Inc.\n"
    "Dunord Technologies\n"
    "Genroco, Inc\n"
    "Vector Fabrics BV\n"
    "VoiceTronix Pty Ltd\n"
    "Dawicontrol Computersysteme GmbH\n"
    "Netpower\n"
    "X-ES, Inc.\n"
    "AuzenTech Co., Ltd.\n"
    "Exacq Technologies\n"
    "XenSource, Inc.\n"
    "GoTView\n"
    "Beholder International Ltd.\n"
    "TBS Technologies (wrong ID)\n"
    "TBS Technologies (wrong ID)\n"
    "SmartInfra Ltd\n"
    "UltraStor\n"
    "c't Magazin fuer Computertechnik\n"
    "Logitec Corp.\n"
    "Teradici Corp.\n"
    "TBS Technologies (wrong ID)\n"
    "Decision Computer International Co.\n"
    "GUANGZHOU MAXSUN INFORMATION TECHNOLOGY CO., LTD.\n"
    "TBS Technologies (wrong ID)\n"
    "Glenfly Tech Co., Ltd.\n"
    "ZT Systems\n"
    "Red Hat, Inc.\n"
    "TBS Technologies (wrong ID)\n"
    "TBS Technologies (wrong ID)\n"
    "TBS Technologies (wrong ID)\n"
    "NOVAIUM Technology\n"
    "pcHDTV\n"
    "HT OMEGA Inc.\n"
    "IOxOS Technologies SA\n"
    "Shenzhen Colorful Yugong Technology and Development Co.\n"
    "EndRun Technologies\n"
    "TP-LINK Technologies Co., Ltd.\n"
    "HongQin (Beijing) Technology Co., Ltd.\n"
    "O.N. Electronic Co Ltd.\n"
    "Herrick Technology Laboratories, Inc. [HTL]\n"
    "MIDAC Corporation\n"
    "Arrow Lake-S PCH CNVi WiFi\n"
    "PowerTV\n"
    "Quancom Electronic GmbH\n"
    "Asustek Computer, Inc.\n"
    "Chengdu Storeswift Technology Co., Ltd.\n"
    "Intel Corporation\n"
    "Beijing Wangxun Technology Co., Ltd.\n"
    "InnoTek Systemberatung GmbH\n"
    "HippStor Technology Co., Ltd\n"
    "Sodick America Corp.\n"
    "SigmaTel\n"
    "Suzhou Yige Technology Co., Ltd.\n"
    "TRENDware International Inc.\n"
    "Sharetronic Data Technology Co., Ltd.\n"
    "Sietium Semiconductor Co., Ltd.\n"
    "SAP\n"
    "Trigem Computer Inc.\n"
    "Stryker Corporation\n"
    "MUCSE\n"
    "T-Square Design Inc.\n"
    "Silicon Magic\n"
    "TRX\n"
    "Winbond\n"
    "Computone Corporation\n"
    "KTI\n"
    "C*Core Technology Co., Ltd.\n"
    "Adaptec\n"
    "Adaptec\n"
    "Atronics\n"
    "Gigapixel Corp\n"
    "Holtek\n"
    "Softlogic Co., Ltd.\n"
    "JusonTech Corporation\n"
    "Omni Media Technology Inc\n"
    "MosChip Semiconductor Technology Ltd.\n"
    "3Com (wrong ID)\n"
    "Stargen Inc.\n"
    "MetaX Integrated Circuits (Shanghai) Co., Ltd.\n"
    "Tiger Lake-H Gaussian & Neural Accelerator\n"
    "Beijing Starblaze Technology Co. Ltd.\n"
    "Asix Electronics Corporation (Wrong ID)\n"
    "AOPEN Inc.\n"
    "UNISYS Corporation\n"
    "NEC Corporation\n"
    "Hewlett Packard\n"
    "Hewlett Packard GmbH PL24-MKT\n"
    "Sony\n"
    "3Com Corporation\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "iTuner\n"
    "Scitex Digital Video\n"
    "Ncomputing X300 PCI-Engine\n"
    "Adnaco Technology Inc.\n"
    "Vadatech Inc.\n"
    "Digital Receiver Technology Inc\n"
    "Actuality Systems\n"
    "Alta Data Technologies LLC\n"
    "Adrienne Electronics Corporation\n"
    "Sirrix AG security technologies\n"
    "OpenVox Communication Co. Ltd.\n"
    "Uakron PCI Project\n"
    "Shiva Europe Limited\n"
    "ATCOM Technology co., LTD.\n"
    "TD3-X3+\n"
    "Pinnacle Systems, Inc. (Wrong ID)\n"
    "Blackmagic Design\n"
    "TSI Telsys\n"
    "Micron/Crucial Technology\n"
    "Motorola\n"
    "Motion Engineering, Inc.\n"
    "I-TEK OptoElectronics Co., LTD.\n"
    "I-TEK OptoElectronics Co., LTD.\n"
    "Cambrionix Ltd.\n"
    "Varian Australia Pty Ltd\n"
    "Cambricon Technologies Corporation Limited\n"
    "CACE Technologies, Inc.\n"
    "Canny Edge\n"
    "Thales\n"
    "ScaleFlux Inc.\n"
    "Catapult Communications\n"
    "Curtiss-Wright Controls Embedded Computing\n"
    "Tyzx, Inc.\n"
    "NextSilicon Ltd\n"
    "KEBA AG\n"
    "Spectrum-4TOR\n"
    "SolidRun\n"
    "Digium, Inc.\n"
    "Ultimarc\n"
    "Chengdu NorthLink Technology Co., Ltd.\n"
    "LeapIO\n"
    "Dy4 Systems Inc\n"
    "I+ME ACTIA GmbH\n"
    "Exsys\n"
    "Datapath Limited\n"
    "Diablo Technologies\n"
    "Dawicontrol GmbH\n"
    "Dynamic Engineering\n"
    "Digital Devices GmbH\n"
    "Indigita Corporation\n"
    "Middle Digital Inc.\n"
    "XIMEA\n"
    "Winbond\n"
    "Tiger Jet Network Inc. / ICP DAS\n"
    "Elcus\n"
    "EKF Elektronik GmbH\n"
    "Xorcom\n"
    "Essence Technology, Inc.\n"
    "Eagle Technology\n"
    "Emerson Automation Solutions\n"
    "RME\n"
    "Aashima Technology B.V.\n"
    "Endace Measurement Systems, Ltd\n"
    "Belkin Corporation\n"
    "Echo Digital Audio Corporation\n"
    "ARK Logic Inc\n"
    "Enfabrica\n"
    "ASUSTeK Computer Inc. (Wrong ID)\n"
    "Foxconn International, Inc. (Wrong ID)\n"
    "Framework Computer Inc.\n"
    "Cerio\n"
    "SiFive, Inc.\n"
    "AJA Video\n"
    "F5 Networks, Inc.\n"
    "ASRock Incorporation (Wrong ID)\n"
    "Interagon AS\n"
    "Fabric7 Systems, Inc.\n"
    "TenaFe, Inc.\n"
    "Ultraview Corp.\n"
    "Broadcom Inc\n"
    "Fedetec Inc.\n"
    "Suzhou XiongLi Technology Inc.\n"
    "XenSource, Inc.\n"
    "VMWare Inc (temporary ID)\n"
    "Illegal Vendor ID\n"
    ;

static const struct {
    uint16_t id;
    uint16_t name_off;
} vendor_table[2503] = {
    { 0x0001,     0 },
    { 0x0010,    19 },
    { 0x0014,    50 },
    { 0x0018,    74 },
    { 0x001C,   101 },
    { 0x0029,   126 },
    { 0x003D,   136 },
    { 0x0059,   166 },
    { 0x0070,   200 },
    { 0x0071,   230 },
    { 0x0095,   254 },
    { 0x00A7,   285 },
    { 0x0100,   305 },
    { 0x0123,   322 },
    { 0x0127,   339 },
    { 0x0128,   344 },
    { 0x018A,   360 },
    { 0x01DE,   369 },
    { 0x0200,   392 },
    { 0x021B,   408 },
    { 0x025E,   436 },
    { 0x0270,   445 },
    { 0x0291,   486 },
    { 0x02AC,   525 },
    { 0x02E0,   537 },
    { 0x0303,   568 },
    { 0x0308,   603 },
    { 0x0315,   647 },
    { 0x031E,   672 },
    { 0x0357,   678 },
    { 0x0432,   715 },
    { 0x0489,   738 },
    { 0x0497,   745 },
    { 0x05B7,   766 },
    { 0x060E,   772 },
    { 0x0675,   787 },
    { 0x0709,   796 },
    { 0x0721,   813 },
    { 0x0731,   828 },
    { 0x0771,   860 },
    { 0x0777,   904 },
    { 0x0795,   928 },
    { 0x07D1,   939 },
    { 0x0824,   957 },
    { 0x0911,   975 },
    { 0x0925,   983 },
    { 0x0A89,  1017 },
    { 0x0B0B,  1039 },
    { 0x0BAE,  1061 },
    { 0x0CCD,  1086 },
    { 0x0E11,  1111 },
    { 0x0E55,  1139 },
    { 0x0E8D,  1152 },
    { 0x0EAC,  1177 },
    { 0x0F62,  1211 },
    { 0x1000,  1240 },
    { 0x1001,  1255 },
    { 0x1002,  1273 },
    { 0x1003,  1312 },
    { 0x1004,  1325 },
    { 0x1005,  1345 },
    { 0x1006,  1369 },
    { 0x1007,  1381 },
    { 0x1008,  1402 },
    { 0x100A,  1408 },
    { 0x100B,  1429 },
    { 0x100C,  1464 },
    { 0x100D,  1479 },
    { 0x100E,  1496 },
    { 0x1010,  1503 },
    { 0x1011,  1521 },
    { 0x1012,  1551 },
    { 0x1013,  1575 },
    { 0x1014,  1588 },
    { 0x1015,  1592 },
    { 0x1016,  1617 },
    { 0x1017,  1638 },
    { 0x1018,  1655 },
    { 0x1019,  1670 },
    { 0x101A,  1698 },
    { 0x101B,  1713 },
    { 0x101C,  1735 },
    { 0x101D,  1751 },
    { 0x101E,  1777 },
    { 0x101F,  1802 },
    { 0x1020,  1813 },
    { 0x1021,  1839 },
    { 0x1022,  1870 },
    { 0x1023,  1905 },
    { 0x1024,  1926 },
    { 0x1025,  1976 },
    { 0x1028,  2000 },
    { 0x1029,  2005 },
    { 0x102A,  2024 },
    { 0x102B,  2034 },
    { 0x102C,  2066 },
    { 0x102D,  2089 },
    { 0x102E,  2110 },
    { 0x102F,  2139 },
    { 0x1030,  2155 },
    { 0x1031,  2168 },
    { 0x1032,  2194 },
    { 0x1033,  2201 },
    { 0x1034,  2217 },
    { 0x1035,  2247 },
    { 0x1036,  2274 },
    { 0x1037,  2294 },
    { 0x1038,  2316 },
    { 0x1039,  2325 },
    { 0x103A,  2358 },
    { 0x103B,  2382 },
    { 0x103C,  2406 },
    { 0x103E,  2430 },
    { 0x103F,  2451 },
    { 0x1040,  2481 },
    { 0x1041,  2500 },
    { 0x1042,  2511 },
    { 0x1043,  2518 },
    { 0x1044,  2540 },
    { 0x1045,  2563 },
    { 0x1046,  2573 },
    { 0x1047,  2595 },
    { 0x1048,  2614 },
    { 0x1049,  2622 },
    { 0x104A,  2650 },
    { 0x104B,  2669 },
    { 0x104C,  2678 },
    { 0x104D,  2696 },
    { 0x104E,  2713 },
    { 0x104F,  2733 },
    { 0x1050,  2754 },
    { 0x1051,  2779 },
    { 0x1052,  2792 },
    { 0x1053,  2813 },
    { 0x1054,  2833 },
    { 0x1055,  2846 },
    { 0x1056,  2874 },
    { 0x1057,  2878 },
    { 0x1058,  2887 },
    { 0x1059,  2924 },
    { 0x105A,  2932 },
    { 0x105B,  2957 },
    { 0x105C,  2985 },
    { 0x105D,  3008 },
    { 0x105E,  3034 },
    { 0x105F,  3054 },
    { 0x1060,  3077 },
    { 0x1061,  3107 },
    { 0x1062,  3114 },
    { 0x1063,  3135 },
    { 0x1064,  3159 },
    { 0x1065,  3167 },
    { 0x1066,  3186 },
    { 0x1067,  3207 },
    { 0x1068,  3227 },
    { 0x1069,  3250 },
    { 0x106A,  3268 },
    { 0x106B,  3286 },
    { 0x106C,  3297 },
    { 0x106D,  3317 },
    { 0x106E,  3342 },
    { 0x106F,  3351 },
    { 0x1070,  3377 },
    { 0x1071,  3396 },
    { 0x1072,  3402 },
    { 0x1073,  3413 },
    { 0x1074,  3432 },
    { 0x1075,  3452 },
    { 0x1076,  3483 },
    { 0x1077,  3510 },
    { 0x1078,  3523 },
    { 0x1079,  3541 },
    { 0x107A,  3547 },
    { 0x107B,  3556 },
    { 0x107C,  3570 },
    { 0x107D,  3610 },
    { 0x107E,  3632 },
    { 0x107F,  3655 },
    { 0x1080,  3683 },
    { 0x1081,  3703 },
    { 0x1082,  3723 },
    { 0x1083,  3750 },
    { 0x1084,  3777 },
    { 0x1086,  3785 },
    { 0x1087,  3810 },
    { 0x1088,  3825 },
    { 0x1089,  3855 },
    { 0x108A,  3880 },
    { 0x108C,  3897 },
    { 0x108D,  3919 },
    { 0x108E,  3926 },
    { 0x108F,  3937 },
    { 0x1090,  3948 },
    { 0x1091,  3979 },
    { 0x1092,  4002 },
    { 0x1093,  4029 },
    { 0x1094,  4050 },
    { 0x1095,  4086 },
    { 0x1096,  4106 },
    { 0x1097,  4114 },
    { 0x1098,  4132 },
    { 0x1099,  4159 },
    { 0x109A,  4188 },
    { 0x109B,  4201 },
    { 0x109C,  4224 },
    { 0x109D,  4246 },
    { 0x109E,  4269 },
    { 0x109F,  4291 },
    { 0x10A0,  4312 },
    { 0x10A1,  4334 },
    { 0x10A2,  4364 },
    { 0x10A3,  4384 },
    { 0x10A4,  4403 },
    { 0x10A5,  4429 },
    { 0x10A6,  4445 },
    { 0x10A7,  4472 },
    { 0x10A8,  4499 },
    { 0x10A9,  4520 },
    { 0x10AA,  4549 },
    { 0x10AB,  4570 },
    { 0x10AC,  4578 },
    { 0x10AD,  4592 },
    { 0x10AE,  4633 },
    { 0x10AF,  4656 },
    { 0x10B0,  4683 },
    { 0x10B1,  4705 },
    { 0x10B2,  4727 },
    { 0x10B3,  4744 },
    { 0x10B4,  4757 },
    { 0x10B5,  4773 },
    { 0x10B6,  4794 },
    { 0x10B7,  4809 },
    { 0x10B8,  4826 },
    { 0x10B9,  4859 },
    { 0x10BA,  4880 },
    { 0x10BB,  4906 },
    { 0x10BC,  4936 },
    { 0x10BD,  4960 },
    { 0x10BE,  4979 },
    { 0x10BF,  5008 },
    { 0x10C0,  5017 },
    { 0x10C1,  5036 },
    { 0x10C2,  5050 },
    { 0x10C3,  5070 },
    { 0x10C4,  5099 },
    { 0x10C5,  5133 },
    { 0x10C6,  5151 },
    { 0x10C7,  5163 },
    { 0x10C8,  5176 },
    { 0x10C9,  5197 },
    { 0x10CA,  5220 },
    { 0x10CB,  5247 },
    { 0x10CC,  5265 },
    { 0x10CD,  5288 },
    { 0x10CE,  5318 },
    { 0x10CF,  5325 },
    { 0x10D1,  5342 },
    { 0x10D2,  5367 },
    { 0x10D3,  5386 },
    { 0x10D4,  5404 },
    { 0x10D5,  5428 },
    { 0x10D6,  5443 },
    { 0x10D7,  5449 },
    { 0x10D8,  5471 },
    { 0x10D9,  5497 },
    { 0x10DA,  5519 },
    { 0x10DB,  5537 },
    { 0x10DC,  5560 },
    { 0x10DD,  5573 },
    { 0x10DE,  5592 },
    { 0x10DF,  5611 },
    { 0x10E0,  5630 },
    { 0x10E1,  5662 },
    { 0x10E2,  5689 },
    { 0x10E3,  5707 },
    { 0x10E4,  5734 },
    { 0x10E5,  5751 },
    { 0x10E6,  5780 },
    { 0x10E7,  5812 },
    { 0x10E8,  5818 },
    { 0x10E9,  5847 },
    { 0x10EA,  5871 },
    { 0x10EB,  5884 },
    { 0x10EC,  5901 },
    { 0x10ED,  5933 },
    { 0x10EE,  5951 },
    { 0x10EF,  5970 },
    { 0x10F0,  6001 },
    { 0x10F1,  6021 },
    { 0x10F2,  6035 },
    { 0x10F3,  6056 },
    { 0x10F4,  6069 },
    { 0x10F5,  6089 },
    { 0x10F6,  6105 },
    { 0x10F7,  6136 },
    { 0x10F8,  6177 },
    { 0x10F9,  6193 },
    { 0x10FA,  6203 },
    { 0x10FB,  6214 },
    { 0x10FC,  6259 },
    { 0x10FD,  6281 },
    { 0x10FE,  6300 },
    { 0x10FF,  6319 },
    { 0x1100,  6325 },
    { 0x1101,  6341 },
    { 0x1102,  6360 },
    { 0x1103,  6374 },
    { 0x1104,  6403 },
    { 0x1105,  6419 },
    { 0x1106,  6439 },
    { 0x1107,  6462 },
    { 0x1108,  6480 },
    { 0x1109,  6494 },
    { 0x110A,  6525 },
    { 0x110B,  6536 },
    { 0x110C,  6560 },
    { 0x110D,  6586 },
    { 0x110E,  6608 },
    { 0x110F,  6623 },
    { 0x1110,  6639 },
    { 0x1111,  6658 },
    { 0x1112,  6679 },
    { 0x1113,  6703 },
    { 0x1114,  6733 },
    { 0x1115,  6751 },
    { 0x1116,  6759 },
    { 0x1117,  6776 },
    { 0x1118,  6790 },
    { 0x1119,  6807 },
    { 0x111A,  6839 },
    { 0x111B,  6863 },
    { 0x111C,  6891 },
    { 0x111D,  6912 },
    { 0x111E,  6934 },
    { 0x111F,  6940 },
    { 0x1120,  6965 },
    { 0x1121,  6974 },
    { 0x1122,  6980 },
    { 0x1123,  7005 },
    { 0x1124,  7028 },
    { 0x1125,  7046 },
    { 0x1126,  7055 },
    { 0x1127,  7061 },
    { 0x1129,  7078 },
    { 0x112A,  7088 },
    { 0x112B,  7121 },
    { 0x112C,  7152 },
    { 0x112D,  7172 },
    { 0x112E,  7180 },
    { 0x112F,  7212 },
    { 0x1130,  7223 },
    { 0x1131,  7238 },
    { 0x1132,  7261 },
    { 0x1133,  7273 },
    { 0x1134,  7294 },
    { 0x1135,  7319 },
    { 0x1136,  7354 },
    { 0x1137,  7376 },
    { 0x1138,  7394 },
    { 0x1139,  7414 },
    { 0x113A,  7436 },
    { 0x113B,  7444 },
    { 0x113C,  7470 },
    { 0x113D,  7497 },
    { 0x113E,  7523 },
    { 0x113F,  7569 },
    { 0x1140,  7591 },
    { 0x1141,  7606 },
    { 0x1142,  7628 },
    { 0x1143,  7663 },
    { 0x1144,  7677 },
    { 0x1145,  7697 },
    { 0x1146,  7717 },
    { 0x1147,  7733 },
    { 0x1148,  7748 },
    { 0x1149,  7759 },
    { 0x114A,  7782 },
    { 0x114B,  7787 },
    { 0x114C,  7804 },
    { 0x114D,  7814 },
    { 0x114E,  7829 },
    { 0x114F,  7847 },
    { 0x1150,  7866 },
    { 0x1151,  7889 },
    { 0x1152,  7910 },
    { 0x1153,  7918 },
    { 0x1154,  7943 },
    { 0x1155,  7953 },
    { 0x1156,  7973 },
    { 0x1157,  7995 },
    { 0x1158,  8013 },
    { 0x1159,  8029 },
    { 0x115A,  8048 },
    { 0x115B,  8062 },
    { 0x115C,  8080 },
    { 0x115D,  8093 },
    { 0x115E,  8100 },
    { 0x115F,  8119 },
    { 0x1160,  8138 },
    { 0x1161,  8151 },
    { 0x1162,  8163 },
    { 0x1163,  8184 },
    { 0x1164,  8194 },
    { 0x1165,  8228 },
    { 0x1166,  8249 },
    { 0x1167,  8258 },
    { 0x1168,  8279 },
    { 0x1169,  8301 },
    { 0x116A,  8346 },
    { 0x116B,  8369 },
    { 0x116C,  8385 },
    { 0x116D,  8426 },
    { 0x116E,  8442 },
    { 0x116F,  8466 },
    { 0x1170,  8489 },
    { 0x1171,  8510 },
    { 0x1172,  8540 },
    { 0x1173,  8559 },
    { 0x1174,  8578 },
    { 0x1175,  8598 },
    { 0x1176,  8619 },
    { 0x1177,  8636 },
    { 0x1178,  8656 },
    { 0x1179,  8667 },
    { 0x117A,  8687 },
    { 0x117B,  8706 },
    { 0x117C,  8728 },
    { 0x117D,  8750 },
    { 0x117E,  8769 },
    { 0x117F,  8781 },
    { 0x1180,  8808 },
    { 0x1181,  8821 },
    { 0x1183,  8845 },
    { 0x1184,  8858 },
    { 0x1185,  8868 },
    { 0x1186,  8896 },
    { 0x1187,  8914 },
    { 0x1188,  8953 },
    { 0x1189,  8984 },
    { 0x118A,  9014 },
    { 0x118B,  9033 },
    { 0x118C,  9054 },
    { 0x118D,  9069 },
    { 0x118E,  9081 },
    { 0x118F,  9096 },
    { 0x1190,  9108 },
    { 0x1191,  9116 },
    { 0x1192,  9138 },
    { 0x1193,  9157 },
    { 0x1194,  9170 },
    { 0x1195,  9188 },
    { 0x1196,  9205 },
    { 0x1197,  9227 },
    { 0x1198,  9255 },
    { 0x1199,  9274 },
    { 0x119A,  9297 },
    { 0x119B,  9314 },
    { 0x119C,  9331 },
    { 0x119D,  9360 },
    { 0x119E,  9384 },
    { 0x119F,  9414 },
    { 0x11A0,  9442 },
    { 0x11A1,  9470 },
    { 0x11A2,  9495 },
    { 0x11A3,  9526 },
    { 0x11A4,  9559 },
    { 0x11A5,  9577 },
    { 0x11A6,  9605 },
    { 0x11A7,  9620 },
    { 0x11A8,  9642 },
    { 0x11A9,  9656 },
    { 0x11AA,  9669 },
    { 0x11AB,  9675 },
    { 0x11AC,  9705 },
    { 0x11AD,  9746 },
    { 0x11AE,  9773 },
    { 0x11AF,  9791 },
    { 0x11B0,  9812 },
    { 0x11B1,  9834 },
    { 0x11B2,  9852 },
    { 0x11B3,  9866 },
    { 0x11B4,  9884 },
    { 0x11B5,  9916 },
    { 0x11B6,  9940 },
    { 0x11B7,  9958 },
    { 0x11B8,  9967 },
    { 0x11B9,  9992 },
    { 0x11BA, 10018 },
    { 0x11BB, 10033 },
    { 0x11BC, 10052 },
    { 0x11BD, 10076 },
    { 0x11BE, 10098 },
    { 0x11BF, 10130 },
    { 0x11C0, 10148 },
    { 0x11C1, 10164 },
    { 0x11C2, 10180 },
    { 0x11C3, 10202 },
    { 0x11C4, 10218 },
    { 0x11C5, 10245 },
    { 0x11C6, 10263 },
    { 0x11C7, 10293 },
    { 0x11C8, 10313 },
    { 0x11C9, 10347 },
    { 0x11CA, 10353 },
    { 0x11CB, 10379 },
    { 0x11CC, 10403 },
    { 0x11CD, 10438 },
    { 0x11CE, 10465 },
    { 0x11CF, 10475 },
    { 0x11D0, 10506 },
    { 0x11D1, 10547 },
    { 0x11D2, 10558 },
    { 0x11D3, 10572 },
    { 0x11D4, 10593 },
    { 0x11D5, 10608 },
    { 0x11D6, 10625 },
    { 0x11D7, 10641 },
    { 0x11D8, 10666 },
    { 0x11D9, 10697 },
    { 0x11DA, 10713 },
    { 0x11DB, 10720 },
    { 0x11DC, 10741 },
    { 0x11DD, 10761 },
    { 0x11DE, 10791 },
    { 0x11DF, 10809 },
    { 0x11E0, 10822 },
    { 0x11E1, 10846 },
    { 0x11E2, 10868 },
    { 0x11E3, 10904 },
    { 0x11E4, 10927 },
    { 0x11E5, 10943 },
    { 0x11E6, 10958 },
    { 0x11E7, 10987 },
    { 0x11E8, 11018 },
    { 0x11E9, 11050 },
    { 0x11EA, 11073 },
    { 0x11EB, 11086 },
    { 0x11EC, 11101 },
    { 0x11ED, 11112 },
    { 0x11EE, 11124 },
    { 0x11EF, 11149 },
    { 0x11F0, 11175 },
    { 0x11F1, 11187 },
    { 0x11F2, 11205 },
    { 0x11F3, 11228 },
    { 0x11F4, 11247 },
    { 0x11F5, 11275 },
    { 0x11F6, 11307 },
    { 0x11F7, 11314 },
    { 0x11F8, 11333 },
    { 0x11F9, 11354 },
    { 0x11FA, 11365 },
    { 0x11FB, 11397 },
    { 0x11FC, 11407 },
    { 0x11FD, 11421 },
    { 0x11FE, 11445 },
    { 0x11FF, 11459 },
    { 0x1200, 11477 },
    { 0x1201, 11493 },
    { 0x1202, 11513 },
    { 0x1203, 11535 },
    { 0x1204, 11568 },
    { 0x1205, 11602 },
    { 0x1206, 11620 },
    { 0x1208, 11639 },
    { 0x1209, 11653 },
    { 0x120A, 11669 },
    { 0x120B, 11678 },
    { 0x120C, 11697 },
    { 0x120D, 11713 },
    { 0x120E, 11736 },
    { 0x120F, 11757 },
    { 0x1210, 11782 },
    { 0x1211, 11809 },
    { 0x1213, 11823 },
    { 0x1214, 11857 },
    { 0x1215, 11888 },
    { 0x1216, 11907 },
    { 0x1217, 11926 },
    { 0x1218, 11941 },
    { 0x1219, 11956 },
    { 0x121A, 11982 },
    { 0x121B, 12005 },
    { 0x121C, 12041 },
    { 0x121D, 12061 },
    { 0x121E, 12092 },
    { 0x121F, 12097 },
    { 0x1220, 12120 },
    { 0x1221, 12138 },
    { 0x1222, 12154 },
    { 0x1223, 12181 },
    { 0x1224, 12212 },
    { 0x1225, 12231 },
    { 0x1227, 12247 },
    { 0x1228, 12269 },
    { 0x1229, 12294 },
    { 0x122A, 12312 },
    { 0x122B, 12331 },
    { 0x122C, 12362 },
    { 0x122D, 12373 },
    { 0x122E, 12391 },
    { 0x122F, 12399 },
    { 0x1230, 12418 },
    { 0x1231, 12439 },
    { 0x1232, 12462 },
    { 0x1233, 12474 },
    { 0x1235, 12489 },
    { 0x1236, 12516 },
    { 0x1237, 12542 },
    { 0x1238, 12570 },
    { 0x1239, 12577 },
    { 0x123A, 12589 },
    { 0x123B, 12616 },
    { 0x123C, 12638 },
    { 0x123D, 12660 },
    { 0x123E, 12690 },
    { 0x123F, 12705 },
    { 0x1240, 12715 },
    { 0x1241, 12743 },
    { 0x1242, 12762 },
    { 0x1243, 12778 },
    { 0x1244, 12786 },
    { 0x1245, 12795 },
    { 0x1246, 12808 },
    { 0x1247, 12833 },
    { 0x1248, 12854 },
    { 0x1249, 12879 },
    { 0x124A, 12909 },
    { 0x124B, 12929 },
    { 0x124C, 12957 },
    { 0x124D, 12985 },
    { 0x124E, 13013 },
    { 0x124F, 13020 },
    { 0x1250, 13048 },
    { 0x1251, 13081 },
    { 0x1253, 13099 },
    { 0x1254, 13127 },
    { 0x1255, 13147 },
    { 0x1256, 13160 },
    { 0x1257, 13187 },
    { 0x1258, 13209 },
    { 0x1259, 13224 },
    { 0x125A, 13239 },
    { 0x125B, 13257 },
    { 0x125C, 13286 },
    { 0x125D, 13312 },
    { 0x125E, 13327 },
    { 0x125F, 13356 },
    { 0x1260, 13386 },
    { 0x1261, 13407 },
    { 0x1262, 13456 },
    { 0x1263, 13482 },
    { 0x1264, 13498 },
    { 0x1265, 13524 },
    { 0x1266, 13549 },
    { 0x1267, 13571 },
    { 0x1268, 13596 },
    { 0x1269, 13606 },
    { 0x126A, 13613 },
    { 0x126B, 13641 },
    { 0x126C, 13652 },
    { 0x126D, 13669 },
    { 0x126E, 13693 },
    { 0x126F, 13725 },
    { 0x1270, 13746 },
    { 0x1271, 13772 },
    { 0x1272, 13787 },
    { 0x1273, 13812 },
    { 0x1274, 13835 },
    { 0x1275, 13843 },
    { 0x1276, 13873 },
    { 0x1277, 13909 },
    { 0x1278, 13919 },
    { 0x1279, 13951 },
    { 0x127A, 13973 },
    { 0x127B, 13996 },
    { 0x127C, 14015 },
    { 0x127D, 14042 },
    { 0x127E, 14056 },
    { 0x127F, 14069 },
    { 0x1280, 14078 },
    { 0x1281, 14101 },
    { 0x1282, 14131 },
    { 0x1283, 14159 },
    { 0x1284, 14195 },
    { 0x1285, 14217 },
    { 0x1286, 14245 },
    { 0x1287, 14256 },
    { 0x1288, 14269 },
    { 0x1289, 14290 },
    { 0x128A, 14311 },
    { 0x128B, 14337 },
    { 0x128C, 14360 },
    { 0x128D, 14378 },
    { 0x128E, 14396 },
    { 0x128F, 14439 },
    { 0x1290, 14459 },
    { 0x1291, 14485 },
    { 0x1292, 14505 },
    { 0x1293, 14534 },
    { 0x1294, 14559 },
    { 0x1295, 14574 },
    { 0x1296, 14598 },
    { 0x1297, 14619 },
    { 0x1298, 14661 },
    { 0x1299, 14697 },
    { 0x129A, 14723 },
    { 0x129B, 14736 },
    { 0x129C, 14749 },
    { 0x129D, 14756 },
    { 0x129E, 14782 },
    { 0x129F, 14812 },
    { 0x12A0, 14838 },
    { 0x12A1, 14860 },
    { 0x12A2, 14885 },
    { 0x12A3, 14912 },
    { 0x12A4, 14932 },
    { 0x12A5, 14967 },
    { 0x12A6, 14988 },
    { 0x12A7, 15012 },
    { 0x12A8, 15021 },
    { 0x12A9, 15034 },
    { 0x12AA, 15054 },
    { 0x12AB, 15079 },
    { 0x12AC, 15116 },
    { 0x12AD, 15137 },
    { 0x12AE, 15152 },
    { 0x12AF, 15173 },
    { 0x12B0, 15189 },
    { 0x12B1, 15211 },
    { 0x12B2, 15221 },
    { 0x12B3, 15245 },
    { 0x12B4, 15263 },
    { 0x12B5, 15277 },
    { 0x12B6, 15298 },
    { 0x12B7, 15319 },
    { 0x12B8, 15338 },
    { 0x12B9, 15343 },
    { 0x12BA, 15369 },
    { 0x12BB, 15384 },
    { 0x12BC, 15411 },
    { 0x12BD, 15430 },
    { 0x12BE, 15446 },
    { 0x12BF, 15464 },
    { 0x12C0, 15486 },
    { 0x12C1, 15494 },
    { 0x12C2, 15512 },
    { 0x12C3, 15527 },
    { 0x12C4, 15555 },
    { 0x12C5, 15572 },
    { 0x12C6, 15602 },
    { 0x12C7, 15621 },
    { 0x12C8, 15635 },
    { 0x12C9, 15651 },
    { 0x12CA, 15667 },
    { 0x12CB, 15696 },
    { 0x12CC, 15726 },
    { 0x12CD, 15759 },
    { 0x12CE, 15768 },
    { 0x12CF, 15782 },
    { 0x12D0, 15804 },
    { 0x12D1, 15822 },
    { 0x12D2, 15830 },
    { 0x12D3, 15867 },
    { 0x12D4, 15885 },
    { 0x12D5, 15910 },
    { 0x12D6, 15935 },
    { 0x12D7, 15949 },
    { 0x12D8, 15963 },
    { 0x12D9, 15985 },
    { 0x12DA, 15996 },
    { 0x12DB, 16011 },
    { 0x12DC, 16040 },
    { 0x12DD, 16077 },
    { 0x12DE, 16097 },
    { 0x12DF, 16118 },
    { 0x12E0, 16139 },
    { 0x12E1, 16154 },
    { 0x12E2, 16171 },
    { 0x12E3, 16206 },
    { 0x12E4, 16245 },
    { 0x12E5, 16271 },
    { 0x12E6, 16294 },
    { 0x12E7, 16308 },
    { 0x12E8, 16330 },
    { 0x12E9, 16341 },
    { 0x12EA, 16353 },
    { 0x12EB, 16359 },
    { 0x12EC, 16380 },
    { 0x12ED, 16403 },
    { 0x12EE, 16419 },
    { 0x12EF, 16432 },
    { 0x12F0, 16447 },
    { 0x12F1, 16454 },
    { 0x12F2, 16474 },
    { 0x12F3, 16492 },
    { 0x12F4, 16512 },
    { 0x12F5, 16520 },
    { 0x12F6, 16526 },
    { 0x12F7, 16540 },
    { 0x12F8, 16547 },
    { 0x12F9, 16570 },
    { 0x12FB, 16584 },
    { 0x12FC, 16611 },
    { 0x12FD, 16634 },
    { 0x12FE, 16638 },
    { 0x12FF, 16672 },
    { 0x1300, 16680 },
    { 0x1302, 16716 },
    { 0x1303, 16739 },
    { 0x1304, 16762 },
    { 0x1305, 16779 },
    { 0x1306, 16793 },
    { 0x1307, 16811 },
    { 0x1308, 16833 },
    { 0x1309, 16856 },
    { 0x130A, 16877 },
    { 0x130B, 16911 },
    { 0x130C, 16944 },
    { 0x130D, 16968 },
    { 0x130E, 16982 },
    { 0x130F, 17009 },
    { 0x1310, 17021 },
    { 0x1311, 17028 },
    { 0x1312, 17045 },
    { 0x1313, 17065 },
    { 0x1315, 17086 },
    { 0x1316, 17094 },
    { 0x1317, 17107 },
    { 0x1318, 17114 },
    { 0x1319, 17134 },
    { 0x131A, 17150 },
    { 0x131C, 17164 },
    { 0x131D, 17200 },
    { 0x131E, 17213 },
    { 0x131F, 17232 },
    { 0x1320, 17241 },
    { 0x1321, 17251 },
    { 0x1322, 17271 },
    { 0x1323, 17284 },
    { 0x1324, 17293 },
    { 0x1325, 17315 },
    { 0x1326, 17339 },
    { 0x1327, 17363 },
    { 0x1328, 17379 },
    { 0x1329, 17402 },
    { 0x132A, 17427 },
    { 0x132B, 17441 },
    { 0x132C, 17464 },
    { 0x132D, 17475 },
    { 0x1330, 17509 },
    { 0x1331, 17522 },
    { 0x1332, 17542 },
    { 0x1334, 17555 },
    { 0x1335, 17584 },
    { 0x1337, 17599 },
    { 0x1338, 17623 },
    { 0x133A, 17638 },
    { 0x133B, 17648 },
    { 0x133C, 17669 },
    { 0x133D, 17684 },
    { 0x133E, 17700 },
    { 0x133F, 17722 },
    { 0x1340, 17739 },
    { 0x1341, 17751 },
    { 0x1342, 17774 },
    { 0x1343, 17793 },
    { 0x1344, 17819 },
    { 0x1345, 17841 },
    { 0x1347, 17853 },
    { 0x1349, 17861 },
    { 0x134A, 17896 },
    { 0x134B, 17917 },
    { 0x134C, 17936 },
    { 0x134D, 17962 },
    { 0x134E, 17972 },
    { 0x134F, 17977 },
    { 0x1350, 17996 },
    { 0x1351, 18011 },
    { 0x1353, 18021 },
    { 0x1354, 18040 },
    { 0x1355, 18057 },
    { 0x1356, 18079 },
    { 0x1359, 18094 },
    { 0x135A, 18109 },
    { 0x135B, 18124 },
    { 0x135C, 18136 },
    { 0x135D, 18148 },
    { 0x135E, 18171 },
    { 0x135F, 18192 },
    { 0x1360, 18217 },
    { 0x1361, 18236 },
    { 0x1362, 18257 },
    { 0x1363, 18279 },
    { 0x1364, 18302 },
    { 0x1365, 18325 },
    { 0x1366, 18340 },
    { 0x1367, 18361 },
    { 0x1368, 18387 },
    { 0x1369, 18407 },
    { 0x136A, 18416 },
    { 0x136B, 18431 },
    { 0x136C, 18458 },
    { 0x136D, 18486 },
    { 0x136F, 18499 },
    { 0x1370, 18517 },
    { 0x1371, 18530 },
    { 0x1373, 18550 },
    { 0x1374, 18569 },
    { 0x1375, 18582 },
    { 0x1376, 18598 },
    { 0x1377, 18602 },
    { 0x1378, 18654 },
    { 0x1379, 18671 },
    { 0x137A, 18703 },
    { 0x137B, 18727 },
    { 0x137C, 18738 },
    { 0x137D, 18761 },
    { 0x137E, 18782 },
    { 0x137F, 18813 },
    { 0x1380, 18841 },
    { 0x1381, 18867 },
    { 0x1382, 18882 },
    { 0x1383, 18913 },
    { 0x1384, 18928 },
    { 0x1385, 18959 },
    { 0x1386, 18967 },
    { 0x1387, 18993 },
    { 0x1388, 19006 },
    { 0x1389, 19044 },
    { 0x138A, 19067 },
    { 0x138B, 19090 },
    { 0x138C, 19102 },
    { 0x138D, 19118 },
    { 0x138E, 19148 },
    { 0x138F, 19160 },
    { 0x1390, 19181 },
    { 0x1391, 19205 },
    { 0x1392, 19230 },
    { 0x1393, 19245 },
    { 0x1394, 19270 },
    { 0x1395, 19295 },
    { 0x1396, 19307 },
    { 0x1397, 19326 },
    { 0x1398, 19352 },
    { 0x1399, 19368 },
    { 0x139A, 19388 },
    { 0x139B, 19403 },
    { 0x139C, 19437 },
    { 0x139D, 19452 },
    { 0x139E, 19464 },
    { 0x139F, 19471 },
    { 0x13A0, 19485 },
    { 0x13A1, 19503 },
    { 0x13A2, 19533 },
    { 0x13A3, 19560 },
    { 0x13A4, 19570 },
    { 0x13A5, 19581 },
    { 0x13A6, 19607 },
    { 0x13A7, 19621 },
    { 0x13A8, 19630 },
    { 0x13A9, 19641 },
    { 0x13AA, 19683 },
    { 0x13AB, 19706 },
    { 0x13AC, 19732 },
    { 0x13AD, 19760 },
    { 0x13AE, 19770 },
    { 0x13AF, 19789 },
    { 0x13B0, 19798 },
    { 0x13B1, 19812 },
    { 0x13B2, 19831 },
    { 0x13B3, 19852 },
    { 0x13B4, 19871 },
    { 0x13B5, 19887 },
    { 0x13B6, 19891 },
    { 0x13B7, 19901 },
    { 0x13B8, 19919 },
    { 0x13B9, 19947 },
    { 0x13BA, 19961 },
    { 0x13BB, 19980 },
    { 0x13BC, 20005 },
    { 0x13BD, 20024 },
    { 0x13BE, 20042 },
    { 0x13BF, 20071 },
    { 0x13C0, 20085 },
    { 0x13C1, 20107 },
    { 0x13C2, 20117 },
    { 0x13C3, 20148 },
    { 0x13C4, 20165 },
    { 0x13C5, 20179 },
    { 0x13C6, 20201 },
    { 0x13C7, 20224 },
    { 0x13C8, 20249 },
    { 0x13C9, 20261 },
    { 0x13CA, 20279 },
    { 0x13CB, 20298 },
    { 0x13CC, 20319 },
    { 0x13CD, 20325 },
    { 0x13CE, 20356 },
    { 0x13CF, 20366 },
    { 0x13D0, 20391 },
    { 0x13D1, 20418 },
    { 0x13D2, 20437 },
    { 0x13D4, 20458 },
    { 0x13D5, 20484 },
    { 0x13D6, 20498 },
    { 0x13D7, 20521 },
    { 0x13D8, 20553 },
    { 0x13D9, 20572 },
    { 0x13DA, 20594 },
    { 0x13DB, 20622 },
    { 0x13DC, 20658 },
    { 0x13DD, 20679 },
    { 0x13DE, 20701 },
    { 0x13DF, 20726 },
    { 0x13E0, 20737 },
    { 0x13E1, 20753 },
    { 0x13E2, 20784 },
    { 0x13E3, 20814 },
    { 0x13E4, 20823 },
    { 0x13E5, 20836 },
    { 0x13E6, 20856 },
    { 0x13E7, 20876 },
    { 0x13E8, 20893 },
    { 0x13E9, 20918 },
    { 0x13EA, 20945 },
    { 0x13EB, 20966 },
    { 0x13EC, 20995 },
    { 0x13ED, 21008 },
    { 0x13EE, 21028 },
    { 0x13EF, 21061 },
    { 0x13F0, 21075 },
    { 0x13F1, 21114 },
    { 0x13F2, 21139 },
    { 0x13F3, 21165 },
    { 0x13F4, 21202 },
    { 0x13F5, 21224 },
    { 0x13F6, 21248 },
    { 0x13F7, 21272 },
    { 0x13F8, 21296 },
    { 0x13F9, 21318 },
    { 0x13FA, 21348 },
    { 0x13FB, 21369 },
    { 0x13FC, 21380 },
    { 0x13FD, 21415 },
    { 0x13FE, 21433 },
    { 0x13FF, 21451 },
    { 0x1400, 21469 },
    { 0x1401, 21478 },
    { 0x1402, 21493 },
    { 0x1403, 21518 },
    { 0x1404, 21528 },
    { 0x1405, 21553 },
    { 0x1406, 21575 },
    { 0x1407, 21602 },
    { 0x1408, 21624 },
    { 0x1409, 21638 },
    { 0x140A, 21664 },
    { 0x140B, 21681 },
    { 0x140C, 21701 },
    { 0x140D, 21719 },
    { 0x140E, 21749 },
    { 0x140F, 21772 },
    { 0x1410, 21793 },
    { 0x1411, 21807 },
    { 0x1412, 21824 },
    { 0x1413, 21846 },
    { 0x1414, 21855 },
    { 0x1415, 21877 },
    { 0x1416, 21902 },
    { 0x1417, 21931 },
    { 0x1418, 21960 },
    { 0x1419, 21991 },
    { 0x141A, 22012 },
    { 0x141B, 22041 },
    { 0x141D, 22062 },
    { 0x141E, 22082 },
    { 0x141F, 22092 },
    { 0x1420, 22107 },
    { 0x1421, 22123 },
    { 0x1422, 22144 },
    { 0x1423, 22165 },
    { 0x1424, 22189 },
    { 0x1425, 22213 },
    { 0x1426, 22240 },
    { 0x1427, 22265 },
    { 0x1428, 22290 },
    { 0x1429, 22302 },
    { 0x142A, 22324 },
    { 0x142B, 22347 },
    { 0x142C, 22356 },
    { 0x142D, 22385 },
    { 0x142E, 22400 },
    { 0x142F, 22417 },
    { 0x1430, 22438 },
    { 0x1431, 22476 },
    { 0x1432, 22501 },
    { 0x1433, 22521 },
    { 0x1435, 22543 },
    { 0x1436, 22575 },
    { 0x1437, 22594 },
    { 0x1438, 22608 },
    { 0x1439, 22620 },
    { 0x143A, 22653 },
    { 0x143B, 22676 },
    { 0x143C, 22707 },
    { 0x143D, 22719 },
    { 0x143E, 22749 },
    { 0x143F, 22767 },
    { 0x1440, 22799 },
    { 0x1441, 22811 },
    { 0x1442, 22820 },
    { 0x1443, 22847 },
    { 0x1444, 22861 },
    { 0x1445, 22865 },
    { 0x1446, 22880 },
    { 0x1447, 22895 },
    { 0x1448, 22904 },
    { 0x1449, 22930 },
    { 0x144A, 22946 },
    { 0x144B, 22964 },
    { 0x144C, 22984 },
    { 0x144D, 23006 },
    { 0x144E, 23033 },
    { 0x144F, 23040 },
    { 0x1450, 23061 },
    { 0x1451, 23088 },
    { 0x1453, 23110 },
    { 0x1454, 23120 },
    { 0x1455, 23136 },
    { 0x1456, 23156 },
    { 0x1457, 23188 },
    { 0x1458, 23213 },
    { 0x1459, 23242 },
    { 0x145A, 23260 },
    { 0x145B, 23282 },
    { 0x145C, 23292 },
    { 0x145D, 23300 },
    { 0x145E, 23321 },
    { 0x145F, 23345 },
    { 0x1460, 23369 },
    { 0x1461, 23380 },
    { 0x1462, 23407 },
    { 0x1463, 23448 },
    { 0x1464, 23465 },
    { 0x1465, 23500 },
    { 0x1466, 23524 },
    { 0x1467, 23539 },
    { 0x1468, 23551 },
    { 0x1469, 23575 },
    { 0x146A, 23601 },
    { 0x146B, 23610 },
    { 0x146C, 23636 },
    { 0x146D, 23652 },
    { 0x146E, 23666 },
    { 0x146F, 23699 },
    { 0x1470, 23732 },
    { 0x1471, 23745 },
    { 0x1472, 23776 },
    { 0x1473, 23799 },
    { 0x1474, 23822 },
    { 0x1475, 23847 },
    { 0x1476, 23869 },
    { 0x1477, 23892 },
    { 0x1478, 23904 },
    { 0x1479, 23925 },
    { 0x147A, 23946 },
    { 0x147B, 23975 },
    { 0x147C, 23995 },
    { 0x147D, 24007 },
    { 0x147E, 24036 },
    { 0x147F, 24083 },
    { 0x1480, 24102 },
    { 0x1481, 24115 },
    { 0x1482, 24134 },
    { 0x1483, 24174 },
    { 0x1484, 24193 },
    { 0x1485, 24211 },
    { 0x1486, 24234 },
    { 0x1487, 24280 },
    { 0x1489, 24306 },
    { 0x148A, 24330 },
    { 0x148B, 24335 },
    { 0x148C, 24355 },
    { 0x148D, 24384 },
    { 0x148E, 24406 },
    { 0x148F, 24427 },
    { 0x1490, 24449 },
    { 0x1491, 24477 },
    { 0x1492, 24494 },
    { 0x1493, 24517 },
    { 0x1494, 24538 },
    { 0x1495, 24562 },
    { 0x1496, 24600 },
    { 0x1497, 24627 },
    { 0x1498, 24649 },
    { 0x1499, 24672 },
    { 0x149A, 24687 },
    { 0x149B, 24708 },
    { 0x149C, 24730 },
    { 0x149D, 24745 },
    { 0x149E, 24756 },
    { 0x149F, 24780 },
    { 0x14A0, 24795 },
    { 0x14A1, 24808 },
    { 0x14A2, 24826 },
    { 0x14A3, 24853 },
    { 0x14A4, 24871 },
    { 0x14A5, 24902 },
    { 0x14A6, 24936 },
    { 0x14A7, 24965 },
    { 0x14A8, 24984 },
    { 0x14A9, 25017 },
    { 0x14AA, 25030 },
    { 0x14AB, 25058 },
    { 0x14AC, 25089 },
    { 0x14AD, 25114 },
    { 0x14AE, 25134 },
    { 0x14AF, 25143 },
    { 0x14B0, 25165 },
    { 0x14B1, 25198 },
    { 0x14B2, 25211 },
    { 0x14B3, 25233 },
    { 0x14B4, 25243 },
    { 0x14B5, 25277 },
    { 0x14B6, 25292 },
    { 0x14B7, 25311 },
    { 0x14B8, 25322 },
    { 0x14B9, 25349 },
    { 0x14BA, 25387 },
    { 0x14BB, 25401 },
    { 0x14BC, 25421 },
    { 0x14BD, 25450 },
    { 0x14BE, 25470 },
    { 0x14BF, 25488 },
    { 0x14C0, 25515 },
    { 0x14C1, 25538 },
    { 0x14C2, 25551 },
    { 0x14C3, 25564 },
    { 0x14C4, 25579 },
    { 0x14C5, 25614 },
    { 0x14C6, 25637 },
    { 0x14C7, 25651 },
    { 0x14C8, 25683 },
    { 0x14C9, 25704 },
    { 0x14CA, 25725 },
    { 0x14CB, 25740 },
    { 0x14CC, 25763 },
    { 0x14CD, 25793 },
    { 0x14CE, 25840 },
    { 0x14CF, 25863 },
    { 0x14D0, 25885 },
    { 0x14D1, 25904 },
    { 0x14D2, 25928 },
    { 0x14D3, 25950 },
    { 0x14D4, 25967 },
    { 0x14D5, 25991 },
    { 0x14D6, 26011 },
    { 0x14D7, 26023 },
    { 0x14D8, 26045 },
    { 0x14D9, 26066 },
    { 0x14DA, 26101 },
    { 0x14DB, 26133 },
    { 0x14DC, 26156 },
    { 0x14DD, 26178 },
    { 0x14DE, 26202 },
    { 0x14DF, 26234 },
    { 0x14E1, 26259 },
    { 0x14E2, 26268 },
    { 0x14E3, 26279 },
    { 0x14E4, 26287 },
    { 0x14E5, 26318 },
    { 0x14E6, 26334 },
    { 0x14E7, 26357 },
    { 0x14E8, 26361 },
    { 0x14E9, 26372 },
    { 0x14EA, 26394 },
    { 0x14EB, 26421 },
    { 0x14EC, 26438 },
    { 0x14ED, 26459 },
    { 0x14EE, 26476 },
    { 0x14EF, 26495 },
    { 0x14F0, 26522 },
    { 0x14F1, 26550 },
    { 0x14F2, 26573 },
    { 0x14F3, 26594 },
    { 0x14F4, 26605 },
    { 0x14F5, 26638 },
    { 0x14F6, 26648 },
    { 0x14F7, 26672 },
    { 0x14F8, 26692 },
    { 0x14F9, 26707 },
    { 0x14FA, 26725 },
    { 0x14FB, 26745 },
    { 0x14FC, 26769 },
    { 0x14FD, 26782 },
    { 0x14FE, 26810 },
    { 0x14FF, 26831 },
    { 0x1500, 26859 },
    { 0x1501, 26882 },
    { 0x1502, 26902 },
    { 0x1503, 26947 },
    { 0x1504, 26968 },
    { 0x1505, 26987 },
    { 0x1506, 27027 },
    { 0x1507, 27049 },
    { 0x1508, 27068 },
    { 0x1509, 27100 },
    { 0x150A, 27133 },
    { 0x150B, 27153 },
    { 0x150C, 27176 },
    { 0x150D, 27190 },
    { 0x150E, 27204 },
    { 0x150F, 27216 },
    { 0x1510, 27227 },
    { 0x1511, 27255 },
    { 0x1512, 27282 },
    { 0x1513, 27305 },
    { 0x1514, 27313 },
    { 0x1515, 27325 },
    { 0x1516, 27339 },
    { 0x1517, 27360 },
    { 0x1518, 27373 },
    { 0x1519, 27381 },
    { 0x151A, 27414 },
    { 0x151B, 27423 },
    { 0x151C, 27434 },
    { 0x151D, 27457 },
    { 0x151E, 27494 },
    { 0x151F, 27506 },
    { 0x1520, 27531 },
    { 0x1521, 27550 },
    { 0x1522, 27560 },
    { 0x1523, 27573 },
    { 0x1524, 27594 },
    { 0x1525, 27613 },
    { 0x1526, 27633 },
    { 0x1527, 27642 },
    { 0x1528, 27652 },
    { 0x1529, 27659 },
    { 0x152A, 27676 },
    { 0x152B, 27701 },
    { 0x152C, 27727 },
    { 0x152D, 27749 },
    { 0x152E, 27769 },
    { 0x152F, 27779 },
    { 0x1530, 27796 },
    { 0x1531, 27817 },
    { 0x1532, 27829 },
    { 0x1533, 27842 },
    { 0x1534, 27852 },
    { 0x1535, 27862 },
    { 0x1536, 27889 },
    { 0x1537, 27904 },
    { 0x1538, 27926 },
    { 0x1539, 27938 },
    { 0x153A, 27988 },
    { 0x153B, 27998 },
    { 0x153C, 28023 },
    { 0x153D, 28040 },
    { 0x153E, 28053 },
    { 0x153F, 28066 },
    { 0x1540, 28090 },
    { 0x1541, 28117 },
    { 0x1542, 28140 },
    { 0x1543, 28161 },
    { 0x1544, 28182 },
    { 0x1545, 28199 },
    { 0x1546, 28209 },
    { 0x1547, 28229 },
    { 0x1548, 28243 },
    { 0x1549, 28269 },
    { 0x154A, 28300 },
    { 0x154B, 28321 },
    { 0x154C, 28337 },
    { 0x154D, 28359 },
    { 0x154E, 28393 },
    { 0x154F, 28407 },
    { 0x1550, 28429 },
    { 0x1551, 28449 },
    { 0x1552, 28483 },
    { 0x1553, 28501 },
    { 0x1554, 28528 },
    { 0x1555, 28554 },
    { 0x1556, 28567 },
    { 0x1557, 28572 },
    { 0x1558, 28589 },
    { 0x1559, 28610 },
    { 0x155A, 28623 },
    { 0x155B, 28637 },
    { 0x155C, 28663 },
    { 0x155D, 28678 },
    { 0x155E, 28696 },
    { 0x155F, 28715 },
    { 0x1560, 28733 },
    { 0x1561, 28764 },
    { 0x1562, 28781 },
    { 0x1563, 28801 },
    { 0x1564, 28827 },
    { 0x1565, 28865 },
    { 0x1566, 28894 },
    { 0x1567, 28918 },
    { 0x1568, 28927 },
    { 0x1569, 28947 },
    { 0x156A, 28971 },
    { 0x156B, 28985 },
    { 0x156C, 28995 },
    { 0x156D, 29018 },
    { 0x156E, 29033 },
    { 0x156F, 29042 },
    { 0x1570, 29076 },
    { 0x1571, 29092 },
    { 0x1572, 29114 },
    { 0x1573, 29136 },
    { 0x1574, 29153 },
    { 0x1575, 29177 },
    { 0x1576, 29213 },
    { 0x1578, 29226 },
    { 0x1579, 29231 },
    { 0x157A, 29252 },
    { 0x157B, 29277 },
    { 0x157C, 29298 },
    { 0x157D, 29312 },
    { 0x157E, 29329 },
    { 0x157F, 29349 },
    { 0x1580, 29379 },
    { 0x1581, 29399 },
    { 0x1582, 29424 },
    { 0x1583, 29435 },
    { 0x1584, 29457 },
    { 0x1585, 29479 },
    { 0x1586, 29488 },
    { 0x1587, 29500 },
    { 0x1588, 29512 },
    { 0x1589, 29533 },
    { 0x158A, 29563 },
    { 0x158B, 29583 },
    { 0x158C, 29608 },
    { 0x158D, 29653 },
    { 0x158E, 29678 },
    { 0x158F, 29698 },
    { 0x1590, 29710 },
    { 0x1591, 29737 },
    { 0x1592, 29741 },
    { 0x1593, 29755 },
    { 0x1594, 29764 },
    { 0x1595, 29776 },
    { 0x1596, 29794 },
    { 0x1597, 29814 },
    { 0x1598, 29836 },
    { 0x1599, 29857 },
    { 0x159A, 29879 },
    { 0x159B, 29898 },
    { 0x159C, 29922 },
    { 0x159D, 29947 },
    { 0x159E, 29982 },
    { 0x159F, 30006 },
    { 0x15A0, 30029 },
    { 0x15A1, 30045 },
    { 0x15A2, 30069 },
    { 0x15A3, 30094 },
    { 0x15A4, 30102 },
    { 0x15A5, 30111 },
    { 0x15A6, 30127 },
    { 0x15A7, 30164 },
    { 0x15A8, 30180 },
    { 0x15AA, 30224 },
    { 0x15AB, 30236 },
    { 0x15AC, 30259 },
    { 0x15AD, 30286 },
    { 0x15AE, 30293 },
    { 0x15B0, 30320 },
    { 0x15B1, 30346 },
    { 0x15B2, 30368 },
    { 0x15B3, 30392 },
    { 0x15B4, 30414 },
    { 0x15B5, 30424 },
    { 0x15B6, 30438 },
    { 0x15B7, 30463 },
    { 0x15B8, 30476 },
    { 0x15B9, 30491 },
    { 0x15BA, 30522 },
    { 0x15BB, 30546 },
    { 0x15BC, 30559 },
    { 0x15BD, 30580 },
    { 0x15BE, 30588 },
    { 0x15BF, 30605 },
    { 0x15C0, 30635 },
    { 0x15C1, 30643 },
    { 0x15C2, 30651 },
    { 0x15C3, 30672 },
    { 0x15C4, 30693 },
    { 0x15C5, 30702 },
    { 0x15C6, 30726 },
    { 0x15C7, 30759 },
    { 0x15C8, 30793 },
    { 0x15C9, 30812 },
    { 0x15CA, 30834 },
    { 0x15CB, 30845 },
    { 0x15CC, 30864 },
    { 0x15CD, 30876 },
    { 0x15CE, 30893 },
    { 0x15CF, 30904 },
    { 0x15D1, 30952 },
    { 0x15D2, 30977 },
    { 0x15D3, 31016 },
    { 0x15D4, 31044 },
    { 0x15D5, 31055 },
    { 0x15D6, 31065 },
    { 0x15D7, 31079 },
    { 0x15D8, 31100 },
    { 0x15D9, 31130 },
    { 0x15DA, 31155 },
    { 0x15DB, 31169 },
    { 0x15DC, 31199 },
    { 0x15DD, 31212 },
    { 0x15DE, 31225 },
    { 0x15DF, 31252 },
    { 0x15E0, 31268 },
    { 0x15E1, 31282 },
    { 0x15E2, 31311 },
    { 0x15E3, 31337 },
    { 0x15E4, 31363 },
    { 0x15E5, 31379 },
    { 0x15E6, 31403 },
    { 0x15E7, 31413 },
    { 0x15E8, 31434 },
    { 0x15E9, 31457 },
    { 0x15EA, 31478 },
    { 0x15EB, 31502 },
    { 0x15EC, 31539 },
    { 0x15ED, 31553 },
    { 0x15EE, 31567 },
    { 0x15EF, 31590 },
    { 0x15F0, 31615 },
    { 0x15F1, 31634 },
    { 0x15F2, 31654 },
    { 0x15F3, 31681 },
    { 0x15F4, 31697 },
    { 0x15F5, 31707 },
    { 0x15F6, 31728 },
    { 0x15F7, 31754 },
    { 0x15F8, 31762 },
    { 0x15F9, 31782 },
    { 0x15FA, 31806 },
    { 0x15FB, 31822 },
    { 0x15FC, 31832 },
    { 0x15FD, 31859 },
    { 0x15FE, 31871 },
    { 0x15FF, 31893 },
    { 0x1600, 31920 },
    { 0x1601, 31950 },
    { 0x1602, 31967 },
    { 0x1603, 31982 },
    { 0x1604, 32012 },
    { 0x1605, 32043 },
    { 0x1606, 32065 },
    { 0x1607, 32076 },
    { 0x1608, 32113 },
    { 0x1609, 32146 },
    { 0x1612, 32172 },
    { 0x1618, 32198 },
    { 0x1619, 32221 },
    { 0x161F, 32248 },
    { 0x1621, 32257 },
    { 0x1626, 32286 },
    { 0x1629, 32310 },
    { 0x1631, 32332 },
    { 0x1638, 32350 },
    { 0x163C, 32383 },
    { 0x1641, 32399 },
    { 0x1642, 32411 },
    { 0x1657, 32462 },
    { 0x165A, 32476 },
    { 0x165C, 32485 },
    { 0x165D, 32496 },
    { 0x165F, 32529 },
    { 0x1661, 32551 },
    { 0x1665, 32568 },
    { 0x1668, 32577 },
    { 0x166D, 32603 },
    { 0x1677, 32624 },
    { 0x1678, 32655 },
    { 0x1679, 32665 },
    { 0x167B, 32692 },
    { 0x167D, 32715 },
    { 0x167E, 32751 },
    { 0x1681, 32763 },
    { 0x1682, 32772 },
    { 0x1688, 32792 },
    { 0x168A, 32818 },
    { 0x168C, 32834 },
    { 0x1695, 32851 },
    { 0x169C, 32875 },
    { 0x169D, 32895 },
    { 0x16A5, 32917 },
    { 0x16AB, 32944 },
    { 0x16AE, 32970 },
    { 0x16AF, 32982 },
    { 0x16B4, 33012 },
    { 0x16B8, 33036 },
    { 0x16BE, 33062 },
    { 0x16C3, 33085 },
    { 0x16C6, 33100 },
    { 0x16C8, 33114 },
    { 0x16C9, 33127 },
    { 0x16CA, 33154 },
    { 0x16CD, 33166 },
    { 0x16CE, 33184 },
    { 0x16D5, 33197 },
    { 0x16DA, 33211 },
    { 0x16DF, 33231 },
    { 0x16E2, 33254 },
    { 0x16E3, 33276 },
    { 0x16E5, 33298 },
    { 0x16EC, 33313 },
    { 0x16ED, 33327 },
    { 0x16F2, 33340 },
    { 0x16F3, 33350 },
    { 0x16F4, 33379 },
    { 0x16F6, 33389 },
    { 0x1702, 33409 },
    { 0x1705, 33445 },
    { 0x170B, 33465 },
    { 0x170C, 33475 },
    { 0x1719, 33491 },
    { 0x1725, 33511 },
    { 0x172A, 33533 },
    { 0x172F, 33556 },
    { 0x1734, 33583 },
    { 0x1735, 33612 },
    { 0x1737, 33640 },
    { 0x173B, 33648 },
    { 0x1743, 33670 },
    { 0x1745, 33683 },
    { 0x1749, 33702 },
    { 0x174B, 33719 },
    { 0x174D, 33760 },
    { 0x175C, 33777 },
    { 0x175E, 33794 },
    { 0x1760, 33815 },
    { 0x1761, 33835 },
    { 0x1771, 33860 },
    { 0x1775, 33887 },
    { 0x177D, 33904 },
    { 0x1787, 33917 },
    { 0x1789, 33950 },
    { 0x1796, 33976 },
    { 0x1797, 34000 },
    { 0x1799, 34018 },
    { 0x179A, 34025 },
    { 0x179C, 34038 },
    { 0x17A0, 34052 },
    { 0x17AA, 34071 },
    { 0x17AB, 34078 },
    { 0x17AF, 34098 },
    { 0x17B3, 34131 },
    { 0x17B4, 34152 },
    { 0x17C0, 34173 },
    { 0x17C2, 34187 },
    { 0x17C3, 34201 },
    { 0x17CB, 34217 },
    { 0x17CC, 34244 },
    { 0x17CD, 34268 },
    { 0x17CF, 34297 },
    { 0x17D3, 34309 },
    { 0x17D5, 34332 },
    { 0x17DB, 34343 },
    { 0x17DE, 34352 },
    { 0x17DF, 34377 },
    { 0x17E4, 34388 },
    { 0x17E6, 34398 },
    { 0x17EE, 34408 },
    { 0x17F2, 34431 },
    { 0x17F3, 34446 },
    { 0x17F7, 34470 },
    { 0x17F9, 34496 },
    { 0x17FC, 34523 },
    { 0x17FE, 34536 },
    { 0x17FF, 34551 },
    { 0x1800, 34568 },
    { 0x1803, 34588 },
    { 0x1804, 34603 },
    { 0x1805, 34627 },
    { 0x1809, 34640 },
    { 0x180C, 34655 },
    { 0x1813, 34676 },
    { 0x1814, 34701 },
    { 0x1815, 34714 },
    { 0x1820, 34724 },
    { 0x1822, 34747 },
    { 0x182D, 34774 },
    { 0x182E, 34792 },
    { 0x182F, 34820 },
    { 0x1830, 34829 },
    { 0x183B, 34858 },
    { 0x1846, 34870 },
    { 0x1849, 34885 },
    { 0x184A, 34906 },
    { 0x1850, 34923 },
    { 0x1851, 34945 },
    { 0x1852, 34961 },
    { 0x1853, 34975 },
    { 0x1854, 35017 },
    { 0x185B, 35038 },
    { 0x185F, 35062 },
    { 0x1864, 35082 },
    { 0x1867, 35093 },
    { 0x186C, 35116 },
    { 0x186F, 35133 },
    { 0x1876, 35157 },
    { 0x187E, 35176 },
    { 0x1885, 35209 },
    { 0x1888, 35229 },
    { 0x188A, 35241 },
    { 0x1890, 35267 },
    { 0x1894, 35281 },
    { 0x1896, 35289 },
    { 0x1897, 35333 },
    { 0x18A1, 35339 },
    { 0x18A2, 35360 },
    { 0x18A3, 35373 },
    { 0x18AC, 35378 },
    { 0x18B8, 35396 },
    { 0x18BC, 35404 },
    { 0x18C3, 35430 },
    { 0x18C8, 35464 },
    { 0x18C9, 35473 },
    { 0x18CA, 35494 },
    { 0x18D2, 35544 },
    { 0x18D4, 35573 },
    { 0x18D8, 35583 },
    { 0x18DD, 35609 },
    { 0x18DF, 35620 },
    { 0x18E6, 35641 },
    { 0x18EB, 35648 },
    { 0x18EC, 35693 },
    { 0x18EE, 35710 },
    { 0x18F1, 35735 },
    { 0x18F4, 35749 },
    { 0x18F6, 35762 },
    { 0x18F7, 35769 },
    { 0x18FB, 35784 },
    { 0x1904, 35807 },
    { 0x1905, 35849 },
    { 0x1912, 35868 },
    { 0x1919, 35894 },
    { 0x1923, 35915 },
    { 0x1924, 35942 },
    { 0x192A, 35957 },
    { 0x192E, 35980 },
    { 0x1931, 35995 },
    { 0x1932, 36007 },
    { 0x193C, 36014 },
    { 0x193D, 36040 },
    { 0x193F, 36071 },
    { 0x1942, 36090 },
    { 0x1945, 36116 },
    { 0x1947, 36121 },
    { 0x1948, 36134 },
    { 0x194A, 36154 },
    { 0x1954, 36173 },
    { 0x1957, 36196 },
    { 0x1958, 36224 },
    { 0x1959, 36248 },
    { 0x1966, 36261 },
    { 0x1969, 36281 },
    { 0x196A, 36298 },
    { 0x196D, 36320 },
    { 0x196E, 36331 },
    { 0x1971, 36335 },
    { 0x1974, 36360 },
    { 0x1976, 36391 },
    { 0x1977, 36400 },
    { 0x197B, 36407 },
    { 0x1982, 36432 },
    { 0x1987, 36473 },
    { 0x1989, 36504 },
    { 0x198A, 36518 },
    { 0x1993, 36533 },
    { 0x1998, 36569 },
    { 0x1999, 36603 },
    { 0x199A, 36612 },
    { 0x199D, 36629 },
    { 0x199F, 36643 },
    { 0x19A2, 36651 },
    { 0x19A4, 36670 },
    { 0x19A8, 36698 },
    { 0x19AC, 36711 },
    { 0x19AE, 36741 },
    { 0x19BA, 36769 },
    { 0x19C1, 36796 },
    { 0x19D1, 36807 },
    { 0x19D4, 36827 },
    { 0x19DA, 36843 },
    { 0x19DE, 36874 },
    { 0x19E2, 36889 },
    { 0x19E3, 36912 },
    { 0x19E5, 36925 },
    { 0x19E7, 36955 },
    { 0x19EE, 36992 },
    { 0x19F1, 37016 },
    { 0x19FE, 37025 },
    { 0x19FF, 37047 },
    { 0x1A03, 37080 },
    { 0x1A05, 37104 },
    { 0x1A07, 37112 },
    { 0x1A08, 37122 },
    { 0x1A0D, 37143 },
    { 0x1A0E, 37161 },
    { 0x1A17, 37187 },
    { 0x1A1D, 37210 },
    { 0x1A1E, 37220 },
    { 0x1A22, 37240 },
    { 0x1A29, 37252 },
    { 0x1A2B, 37267 },
    { 0x1A30, 37276 },
    { 0x1A32, 37283 },
    { 0x1A3B, 37308 },
    { 0x1A3E, 37318 },
    { 0x1A41, 37344 },
    { 0x1A4A, 37357 },
    { 0x1A51, 37394 },
    { 0x1A55, 37407 },
    { 0x1A56, 37432 },
    { 0x1A57, 37447 },
    { 0x1A58, 37471 },
    { 0x1A5D, 37486 },
    { 0x1A5E, 37495 },
    { 0x1A5F, 37507 },
    { 0x1A68, 37525 },
    { 0x1A71, 37543 },
    { 0x1A73, 37559 },
    { 0x1A76, 37578 },
    { 0x1A77, 37586 },
    { 0x1A78, 37609 },
    { 0x1A84, 37631 },
    { 0x1A88, 37651 },
    { 0x1A8A, 37661 },
    { 0x1A8C, 37678 },
    { 0x1A8E, 37695 },
    { 0x1AA8, 37712 },
    { 0x1AA9, 37726 },
    { 0x1AAB, 37762 },
    { 0x1AAE, 37782 },
    { 0x1AB4, 37804 },
    { 0x1AB6, 37851 },
    { 0x1AB8, 37866 },
    { 0x1AB9, 37882 },
    { 0x1AC1, 37892 },
    { 0x1AC8, 37913 },
    { 0x1ACC, 37930 },
    { 0x1AD7, 37947 },
    { 0x1ADE, 37970 },
    { 0x1AE0, 37987 },
    { 0x1AE3, 38000 },
    { 0x1AE7, 38026 },
    { 0x1AE8, 38048 },
    { 0x1AE9, 38058 },
    { 0x1AEA, 38072 },
    { 0x1AEC, 38084 },
    { 0x1AED, 38109 },
    { 0x1AEE, 38117 },
    { 0x1AF4, 38139 },
    { 0x1AF5, 38153 },
    { 0x1AFA, 38167 },
    { 0x1B00, 38195 },
    { 0x1B03, 38224 },
    { 0x1B08, 38251 },
    { 0x1B0A, 38274 },
    { 0x1B13, 38283 },
    { 0x1B1A, 38294 },
    { 0x1B1C, 38321 },
    { 0x1B21, 38329 },
    { 0x1B26, 38353 },
    { 0x1B2C, 38380 },
    { 0x1B36, 38406 },
    { 0x1B37, 38420 },
    { 0x1B39, 38456 },
    { 0x1B3A, 38467 },
    { 0x1B3E, 38495 },
    { 0x1B40, 38510 },
    { 0x1B47, 38548 },
    { 0x1B4B, 38561 },
    { 0x1B4C, 38591 },
    { 0x1B55, 38597 },
    { 0x1B59, 38608 },
    { 0x1B5E, 38643 },
    { 0x1B61, 38660 },
    { 0x1B66, 38694 },
    { 0x1B6F, 38704 },
    { 0x1B73, 38727 },
    { 0x1B74, 38740 },
    { 0x1B79, 38771 },
    { 0x1B85, 38789 },
    { 0x1B94, 38816 },
    { 0x1B96, 38848 },
    { 0x1B9A, 38864 },
    { 0x1BAA, 38888 },
    { 0x1BAD, 38907 },
    { 0x1BB0, 38918 },
    { 0x1BB1, 38941 },
    { 0x1BB3, 38964 },
    { 0x1BB5, 38975 },
    { 0x1BBF, 39006 },
    { 0x1BC0, 39032 },
    { 0x1BCD, 39053 },
    { 0x1BCF, 39071 },
    { 0x1BD0, 39087 },
    { 0x1BD4, 39109 },
    { 0x1BEE, 39131 },
    { 0x1BEF, 39153 },
    { 0x1BF4, 39160 },
    { 0x1BF5, 39188 },
    { 0x1BFC, 39199 },
    { 0x1BFD, 39209 },
    { 0x1C00, 39216 },
    { 0x1C09, 39265 },
    { 0x1C19, 39275 },
    { 0x1C1C, 39281 },
    { 0x1C1F, 39290 },
    { 0x1C28, 39302 },
    { 0x1C2C, 39329 },
    { 0x1C32, 39345 },
    { 0x1C33, 39371 },
    { 0x1C36, 39387 },
    { 0x1C3B, 39407 },
    { 0x1C44, 39421 },
    { 0x1C4E, 39433 },
    { 0x1C58, 39441 },
    { 0x1C5C, 39452 },
    { 0x1C5F, 39461 },
    { 0x1C63, 39498 },
    { 0x1C67, 39564 },
    { 0x1C7A, 39596 },
    { 0x1C7E, 39600 },
    { 0x1C7F, 39626 },
    { 0x1C8A, 39650 },
    { 0x1C8C, 39667 },
    { 0x1CB0, 39682 },
    { 0x1CB1, 39698 },
    { 0x1CB5, 39717 },
    { 0x1CB8, 39749 },
    { 0x1CC1, 39788 },
    { 0x1CC4, 39815 },
    { 0x1CC5, 39860 },
    { 0x1CC7, 39888 },
    { 0x1CCF, 39915 },
    { 0x1CD2, 39932 },
    { 0x1CD7, 39945 },
    { 0x1CDD, 39984 },
    { 0x1CE4, 40013 },
    { 0x1CF0, 40022 },
    { 0x1CF2, 40029 },
    { 0x1CF7, 40039 },
    { 0x1CFA, 40057 },
    { 0x1CFD, 40077 },
    { 0x1D00, 40086 },
    { 0x1D05, 40099 },
    { 0x1D0F, 40122 },
    { 0x1D17, 40139 },
    { 0x1D18, 40147 },
    { 0x1D1C, 40151 },
    { 0x1D1D, 40175 },
    { 0x1D21, 40185 },
    { 0x1D22, 40190 },
    { 0x1D26, 40207 },
    { 0x1D2A, 40219 },
    { 0x1D37, 40236 },
    { 0x1D39, 40247 },
    { 0x1D40, 40266 },
    { 0x1D44, 40307 },
    { 0x1D49, 40311 },
    { 0x1D4C, 40318 },
    { 0x1D5C, 40333 },
    { 0x1D61, 40354 },
    { 0x1D62, 40370 },
    { 0x1D63, 40392 },
    { 0x1D65, 40420 },
    { 0x1D69, 40449 },
    { 0x1D6A, 40475 },
    { 0x1D6C, 40490 },
    { 0x1D72, 40507 },
    { 0x1D78, 40514 },
    { 0x1D79, 40527 },
    { 0x1D7C, 40555 },
    { 0x1D82, 40570 },
    { 0x1D87, 40595 },
    { 0x1D89, 40625 },
    { 0x1D8F, 40659 },
    { 0x1D92, 40665 },
    { 0x1D93, 40684 },
    { 0x1D94, 40690 },
    { 0x1D95, 40727 },
    { 0x1D97, 40741 },
    { 0x1D9B, 40780 },
    { 0x1DA1, 40801 },
    { 0x1DA2, 40821 },
    { 0x1DA3, 40849 },
    { 0x1DA8, 40866 },
    { 0x1DAD, 40881 },
    { 0x1DB2, 40890 },
    { 0x1DB3, 40912 },
    { 0x1DB7, 40953 },
    { 0x1DBB, 40982 },
    { 0x1DBE, 41000 },
    { 0x1DBF, 41021 },
    { 0x1DC2, 41074 },
    { 0x1DC5, 41103 },
    { 0x1DCD, 41113 },
    { 0x1DCF, 41124 },
    { 0x1DD3, 41160 },
    { 0x1DD4, 41188 },
    { 0x1DD5, 41200 },
    { 0x1DD8, 41231 },
    { 0x1DDD, 41252 },
    { 0x1DE0, 41261 },
    { 0x1DE1, 41266 },
    { 0x1DE4, 41293 },
    { 0x1DE5, 41310 },
    { 0x1DED, 41325 },
    { 0x1DEE, 41351 },
    { 0x1DEF, 41386 },
    { 0x1DF3, 41408 },
    { 0x1DF5, 41427 },
    { 0x1DF7, 41455 },
    { 0x1DF8, 41467 },
    { 0x1DFA, 41498 },
    { 0x1DFC, 41516 },
    { 0x1E0B, 41527 },
    { 0x1E0D, 41563 },
    { 0x1E0F, 41586 },
    { 0x1E17, 41605 },
    { 0x1E18, 41658 },
    { 0x1E24, 41710 },
    { 0x1E26, 41734 },
    { 0x1E30, 41767 },
    { 0x1E31, 41774 },
    { 0x1E36, 41791 },
    { 0x1E38, 41827 },
    { 0x1E39, 41839 },
    { 0x1E3A, 41849 },
    { 0x1E3B, 41877 },
    { 0x1E3D, 41898 },
    { 0x1E3E, 41913 },
    { 0x1E43, 41961 },
    { 0x1E44, 41975 },
    { 0x1E48, 41990 },
    { 0x1E49, 41998 },
    { 0x1E4B, 42034 },
    { 0x1E4C, 42067 },
    { 0x1E50, 42082 },
    { 0x1E52, 42104 },
    { 0x1E57, 42120 },
    { 0x1E59, 42154 },
    { 0x1E5D, 42183 },
    { 0x1E60, 42204 },
    { 0x1E67, 42228 },
    { 0x1E68, 42240 },
    { 0x1E6B, 42289 },
    { 0x1E6C, 42302 },
    { 0x1E7B, 42319 },
    { 0x1E7C, 42328 },
    { 0x1E7E, 42342 },
    { 0x1E7F, 42349 },
    { 0x1E81, 42386 },
    { 0x1E83, 42423 },
    { 0x1E85, 42448 },
    { 0x1E89, 42458 },
    { 0x1E93, 42474 },
    { 0x1E94, 42521 },
    { 0x1E95, 42532 },
    { 0x1E96, 42575 },
    { 0x1E9F, 42598 },
    { 0x1EA0, 42627 },
    { 0x1EA7, 42673 },
    { 0x1EAB, 42690 },
    { 0x1EAC, 42731 },
    { 0x1EAE, 42768 },
    { 0x1EB0, 42780 },
    { 0x1EB1, 42815 },
    { 0x1EB4, 42831 },
    { 0x1EB6, 42883 },
    { 0x1EB9, 42926 },
    { 0x1EBD, 42954 },
    { 0x1EC6, 42978 },
    { 0x1EC8, 42998 },
    { 0x1EC9, 43035 },
    { 0x1ECA, 43067 },
    { 0x1ED0, 43079 },
    { 0x1ED2, 43104 },
    { 0x1ED3, 43120 },
    { 0x1ED5, 43127 },
    { 0x1ED8, 43160 },
    { 0x1ED9, 43179 },
    { 0x1EE1, 43189 },
    { 0x1EE4, 43227 },
    { 0x1EE9, 43238 },
    { 0x1EEC, 43247 },
    { 0x1EED, 43272 },
    { 0x1EF6, 43302 },
    { 0x1EF7, 43319 },
    { 0x1EFB, 43367 },
    { 0x1EFF, 43383 },
    { 0x1F02, 43399 },
    { 0x1F03, 43423 },
    { 0x1F0A, 43465 },
    { 0x1F0D, 43493 },
    { 0x1F0F, 43507 },
    { 0x1F16, 43531 },
    { 0x1F17, 43550 },
    { 0x1F18, 43572 },
    { 0x1F1C, 43585 },
    { 0x1F24, 43610 },
    { 0x1F2E, 43649 },
    { 0x1F2F, 43673 },
    { 0x1F31, 43728 },
    { 0x1F32, 43738 },
    { 0x1F3F, 43774 },
    { 0x1F40, 43784 },
    { 0x1F44, 43809 },
    { 0x1F47, 43843 },
    { 0x1F49, 43860 },
    { 0x1F4B, 43875 },
    { 0x1F52, 43904 },
    { 0x1F56, 43920 },
    { 0x1F60, 43932 },
    { 0x1F67, 43942 },
    { 0x1F6C, 43964 },
    { 0x1F73, 43995 },
    { 0x1F7A, 44028 },
    { 0x1F82, 44041 },
    { 0x1F8C, 44050 },
    { 0x1F90, 44064 },
    { 0x1F99, 44084 },
    { 0x1F9D, 44126 },
    { 0x1FA4, 44137 },
    { 0x1FAA, 44179 },
    { 0x1FAB, 44233 },
    { 0x1FB0, 44248 },
    { 0x1FBD, 44274 },
    { 0x1FC0, 44312 },
    { 0x1FC1, 44331 },
    { 0x1FC3, 44345 },
    { 0x1FC9, 44353 },
    { 0x1FCB, 44374 },
    { 0x1FCC, 44403 },
    { 0x1FCE, 44414 },
    { 0x1FD4, 44426 },
    { 0x1FDD, 44442 },
    { 0x1FDE, 44474 },
    { 0x1FE0, 44516 },
    { 0x1FE1, 44537 },
    { 0x1FE4, 44582 },
    { 0x1FE9, 44602 },
    { 0x1FF2, 44609 },
    { 0x1FF4, 44618 },
    { 0x1FF8, 44634 },
    { 0x1FF9, 44667 },
    { 0x1FFF, 44706 },
    { 0x2000, 44724 },
    { 0x2001, 44740 },
    { 0x2003, 44762 },
    { 0x2004, 44778 },
    { 0x201F, 44794 },
    { 0x202C, 44803 },
    { 0x2036, 44815 },
    { 0x203B, 44853 },
    { 0x2042, 44883 },
    { 0x2044, 44919 },
    { 0x2046, 44964 },
    { 0x2048, 45004 },
    { 0x2052, 45043 },
    { 0x2058, 45065 },
    { 0x205C, 45088 },
    { 0x205D, 45127 },
    { 0x205E, 45183 },
    { 0x2061, 45190 },
    { 0x2063, 45208 },
    { 0x206D, 45263 },
    { 0x2077, 45285 },
    { 0x207D, 45292 },
    { 0x208A, 45297 },
    { 0x2094, 45315 },
    { 0x2096, 45355 },
    { 0x2099, 45396 },
    { 0x209B, 45422 },
    { 0x209F, 45449 },
    { 0x20A1, 45464 },
    { 0x20A6, 45477 },
    { 0x20A7, 45489 },
    { 0x20A8, 45504 },
    { 0x20A9, 45533 },
    { 0x20B5, 45555 },
    { 0x20BA, 45594 },
    { 0x20BB, 45635 },
    { 0x20BC, 45652 },
    { 0x20C0, 45682 },
    { 0x20C1, 45698 },
    { 0x20D0, 45731 },
    { 0x20D2, 45769 },
    { 0x20D8, 45785 },
    { 0x20DC, 45811 },
    { 0x20E1, 45849 },
    { 0x20E3, 45888 },
    { 0x20E7, 45904 },
    { 0x20F4, 45911 },
    { 0x20F6, 45920 },
    { 0x20F9, 45965 },
    { 0x2100, 46009 },
    { 0x2105, 46052 },
    { 0x2106, 46095 },
    { 0x2108, 46120 },
    { 0x2114, 46160 },
    { 0x2116, 46173 },
    { 0x2123, 46196 },
    { 0x21B4, 46235 },
    { 0x21C3, 46272 },
    { 0x22B8, 46300 },
    { 0x22DB, 46324 },
    { 0x2304, 46355 },
    { 0x2321, 46389 },
    { 0x2348, 46405 },
    { 0x256C, 46412 },
    { 0x2646, 46447 },
    { 0x270B, 46481 },
    { 0x270F, 46500 },
    { 0x2711, 46527 },
    { 0x2782, 46548 },
    { 0x2955, 46583 },
    { 0x2A15, 46604 },
    { 0x2A18, 46619 },
    { 0x2BD8, 46646 },
    { 0x2FF1, 46678 },
    { 0x3000, 46696 },
    { 0x30C9, 46720 },
    { 0x3100, 46758 },
    { 0x3112, 46772 },
    { 0x3130, 46796 },
    { 0x3142, 46806 },
    { 0x31AB, 46831 },
    { 0x328F, 46837 },
    { 0x3388, 46873 },
    { 0x3411, 46883 },
    { 0x3442, 46910 },
    { 0x3475, 46930 },
    { 0x34BA, 46952 },
    { 0x3513, 46989 },
    { 0x3633, 47015 },
    { 0x369A, 47024 },
    { 0x37D9, 47042 },
    { 0x3842, 47056 },
    { 0x38EF, 47073 },
    { 0x393E, 47080 },
    { 0x3D3D, 47098 },
    { 0x3E08, 47105 },
    { 0x4005, 47126 },
    { 0x4033, 47144 },
    { 0x4040, 47172 },
    { 0x4143, 47192 },
    { 0x4144, 47215 },
    { 0x4149, 47226 },
    { 0x4150, 47240 },
    { 0x415A, 47259 },
    { 0x416C, 47275 },
    { 0x4242, 47301 },
    { 0x4254, 47330 },
    { 0x4321, 47337 },
    { 0x4348, 47379 },
    { 0x434E, 47386 },
    { 0x4444, 47404 },
    { 0x4468, 47430 },
    { 0x4594, 47450 },
    { 0x45FB, 47475 },
    { 0x4624, 47499 },
    { 0x4651, 47535 },
    { 0x4680, 47540 },
    { 0x4843, 47559 },
    { 0x4916, 47592 },
    { 0x4943, 47620 },
    { 0x494F, 47636 },
    { 0x4978, 47661 },
    { 0x4A14, 47679 },
    { 0x4B10, 47686 },
    { 0x4B43, 47700 },
    { 0x4C48, 47712 },
    { 0x4C4D, 47733 },
    { 0x4C52, 47753 },
    { 0x4C53, 47761 },
    { 0x4C54, 47778 },
    { 0x4CA1, 47806 },
    { 0x4D51, 47828 },
    { 0x4D54, 47840 },
    { 0x4D56, 47861 },
    { 0x4DDC, 47877 },
    { 0x4E4C, 47898 },
    { 0x4E58, 47916 },
    { 0x5045, 47930 },
    { 0x5046, 47952 },
    { 0x5053, 47982 },
    { 0x50B2, 48003 },
    { 0x50CE, 48028 },
    { 0x5136, 48060 },
    { 0x5143, 48077 },
    { 0x5145, 48090 },
    { 0x5168, 48104 },
    { 0x5301, 48132 },
    { 0x5333, 48161 },
    { 0x5431, 48178 },
    { 0x544C, 48194 },
    { 0x544D, 48208 },
    { 0x5452, 48225 },
    { 0x5455, 48236 },
    { 0x5456, 48267 },
    { 0x5519, 48275 },
    { 0x5544, 48299 },
    { 0x5555, 48319 },
    { 0x5646, 48332 },
    { 0x5654, 48350 },
    { 0x5678, 48370 },
    { 0x5700, 48403 },
    { 0x5845, 48412 },
    { 0x584D, 48423 },
    { 0x5851, 48443 },
    { 0x5853, 48462 },
    { 0x5854, 48478 },
    { 0x5ACE, 48486 },
    { 0x6205, 48514 },
    { 0x6209, 48542 },
    { 0x631C, 48570 },
    { 0x6356, 48585 },
    { 0x6374, 48595 },
    { 0x6409, 48628 },
    { 0x6549, 48642 },
    { 0x6590, 48657 },
    { 0x6666, 48685 },
    { 0x6688, 48721 },
    { 0x6704, 48771 },
    { 0x6766, 48799 },
    { 0x6899, 48822 },
    { 0x6900, 48833 },
    { 0x6903, 48847 },
    { 0x6909, 48875 },
    { 0x6910, 48903 },
    { 0x6F67, 48931 },
    { 0x7063, 48950 },
    { 0x7284, 48957 },
    { 0x7357, 48971 },
    { 0x7377, 48993 },
    { 0x7401, 49049 },
    { 0x7470, 49069 },
    { 0x7526, 49100 },
    { 0x7604, 49139 },
    { 0x78C0, 49163 },
    { 0x7BDE, 49207 },
    { 0x7F70, 49225 },
    { 0x7FED, 49252 },
    { 0x8008, 49260 },
    { 0x807D, 49284 },
    { 0x8080, 49307 },
    { 0x8086, 49347 },
    { 0x8088, 49365 },
    { 0x80EE, 49402 },
    { 0x8164, 49430 },
    { 0x8322, 49459 },
    { 0x8384, 49480 },
    { 0x8385, 49489 },
    { 0x8401, 49522 },
    { 0x8412, 49551 },
    { 0x8510, 49589 },
    { 0x8686, 49621 },
    { 0x8800, 49625 },
    { 0x8820, 49646 },
    { 0x8848, 49666 },
    { 0x8866, 49672 },
    { 0x8888, 49693 },
    { 0x8912, 49707 },
    { 0x8C4A, 49711 },
    { 0x8E0E, 49719 },
    { 0x8E2E, 49741 },
    { 0x9000, 49745 },
    { 0x9004, 49773 },
    { 0x9005, 49781 },
    { 0x907F, 49789 },
    { 0x919A, 49798 },
    { 0x9412, 49813 },
    { 0x9413, 49820 },
    { 0x9618, 49840 },
    { 0x9699, 49862 },
    { 0x9710, 49888 },
    { 0x9850, 49926 },
    { 0x9902, 49942 },
    { 0x9999, 49955 },
    { 0x9A11, 50002 },
    { 0x9D32, 50045 },
    { 0xA000, 50083 },
    { 0xA0A0, 50123 },
    { 0xA0F1, 50134 },
    { 0xA200, 50153 },
    { 0xA259, 50169 },
    { 0xA25B, 50185 },
    { 0xA304, 50215 },
    { 0xA727, 50220 },
    { 0xAA00, 50237 },
    { 0xAA01, 50244 },
    { 0xAA02, 50251 },
    { 0xAA03, 50258 },
    { 0xAA04, 50265 },
    { 0xAA05, 50272 },
    { 0xAA06, 50279 },
    { 0xAA07, 50286 },
    { 0xAA08, 50293 },
    { 0xAA09, 50300 },
    { 0xAA0A, 50307 },
    { 0xAA0B, 50314 },
    { 0xAA0C, 50321 },
    { 0xAA0D, 50328 },
    { 0xAA0E, 50335 },
    { 0xAA0F, 50342 },
    { 0xAA42, 50349 },
    { 0xAA55, 50370 },
    { 0xAAAA, 50397 },
    { 0xABCD, 50420 },
    { 0xAC1E, 50434 },
    { 0xAC3D, 50466 },
    { 0xAD00, 50484 },
    { 0xAECB, 50511 },
    { 0xAFFE, 50544 },
    { 0xB100, 50576 },
    { 0xB10B, 50607 },
    { 0xB1B3, 50626 },
    { 0xB1D9, 50647 },
    { 0xB390, 50674 },
    { 0xBD11, 50682 },
    { 0xBDBD, 50716 },
    { 0xC001, 50734 },
    { 0xC0A9, 50745 },
    { 0xC0DE, 50771 },
    { 0xC0FE, 50780 },
    { 0xCA01, 50805 },
    { 0xCA02, 50837 },
    { 0xCA3B, 50869 },
    { 0xCA50, 50885 },
    { 0xCABC, 50910 },
    { 0xCACE, 50953 },
    { 0xCAED, 50977 },
    { 0xCAFE, 50988 },
    { 0xCC53, 50995 },
    { 0xCCCC, 51010 },
    { 0xCCEC, 51034 },
    { 0xCDDD, 51077 },
    { 0xCDFA, 51088 },
    { 0xCEBA, 51104 },
    { 0xCF86, 51112 },
    { 0xD063, 51126 },
    { 0xD161, 51135 },
    { 0xD209, 51148 },
    { 0xD20C, 51157 },
    { 0xD405, 51196 },
    { 0xD4D4, 51203 },
    { 0xD531, 51219 },
    { 0xD84D, 51235 },
    { 0xDADA, 51241 },
    { 0xDB10, 51258 },
    { 0xDC93, 51278 },
    { 0xDCBA, 51295 },
    { 0xDD01, 51315 },
    { 0xDEAD, 51336 },
    { 0xDEAF, 51357 },
    { 0xDEDA, 51377 },
    { 0xE000, 51383 },
    { 0xE159, 51391 },
    { 0xE1C5, 51424 },
    { 0xE4BF, 51430 },
    { 0xE4E4, 51450 },
    { 0xE55E, 51457 },
    { 0xEA01, 51482 },
    { 0xEA50, 51499 },
    { 0xEA60, 51528 },
    { 0xEABB, 51532 },
    { 0xEACE, 51556 },
    { 0xEC80, 51588 },
    { 0xECC0, 51607 },
    { 0xEDD8, 51638 },
    { 0xEFAB, 51652 },
    { 0xF043, 51662 },
    { 0xF05B, 51695 },
    { 0xF111, 51734 },
    { 0xF117, 51758 },
    { 0xF15E, 51764 },
    { 0xF1D0, 51777 },
    { 0xF5F5, 51787 },
    { 0xF849, 51805 },
    { 0xFA57, 51837 },
    { 0xFAB7, 51850 },
    { 0xFE19, 51872 },
    { 0xFEBD, 51885 },
    { 0xFEDA, 51901 },
    { 0xFEDE, 51914 },
    { 0xFFE1, 51927 },
    { 0xFFFD, 51958 },
    { 0xFFFE, 51974 },
    { 0xFFFF, 52000 } 
};

const char* pci_vendor_name(uint16_t vendor_id) {
    int lo = 0, hi = 2503 - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (vendor_table[mid].id == vendor_id)
            return &vendor_names[vendor_table[mid].name_off];
        if (vendor_table[mid].id < vendor_id)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return (const char*)0;
}

int pci_vendor_count(void) { return 2503; }
