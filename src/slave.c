#include "def.h"

main()
{
	int mytid;
	char slave_name[NAMESIZE];
	int i, who, masterTid;

	gethostname(slave_name, NAMESIZE);

	mytid = pvm_mytid();


	pvm_recv( -1, MSG_MSTR );
	pvm_upkint(&masterTid, 1, 1 );
	pvm_upkint(&who, 1, 1 );

	

	pvm_initsend(PvmDataDefault);
	pvm_pkint(&mytid, 1, 1);
	pvm_pkstr(slave_name);
	pvm_send(masterTid, MSG_SLV);


	pvm_exit();
}

