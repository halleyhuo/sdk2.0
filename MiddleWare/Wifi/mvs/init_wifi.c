#include <os_wrapper.h>
#include <log.h>
#include <host_apis.h>
#include <cli/cmds/cli_cmd_wifi.h>
#include <httpserver_raw/httpd.h>
#include <SmartConfig/SmartConfig.h>
#include <net_mgr.h>
#include <lwip/sockets.h>
#include <lwip/netif.h>
#include <lwip/ip_addr.h>
#include "lwip/udp.h"
#include "lwip/igmp.h"

void swtich2STAmode(void)
{
	Sta_setting sta;
	MEMSET(&sta, 0 , sizeof(Sta_setting));
	sta.status = TRUE;
	
	if (netmgr_wifi_control_async(SSV6XXX_HWM_STA, NULL, &sta) == SSV6XXX_FAILED)
	{
		//wifi_audio_debug("\nSwtich to STAmode fail\n");
	}
	else
	{
		//wifi_audio_debug("\nSwtich to STAmode success\n");
	}
}

extern u16 g_SconfigChannelMask;
extern u32 g_sconfig_solution;

int16_t  SCONFIGmode_default()
{
	uint16_t channel = 0x3ffe;
	Sta_setting sta;
	MEMSET(&sta, 0 , sizeof(Sta_setting));
	sta.status = TRUE;
	if(netmgr_wifi_control_async(SSV6XXX_HWM_SCONFIG, NULL, &sta)!= SSV6XXX_SUCCESS)
	{
			LOG_PRINTF("SCONFIG mode fail1\r\n");
		return -1;
	}
		
	vTaskDelay(2000);  //¹Ø¼üdelay
		
	g_sconfig_solution=WECHAT_AIRKISS_IN_FW;
		
	if(netmgr_wifi_sconfig_async(channel)!= SSV6XXX_SUCCESS)
	{
			LOG_PRINTF("SCONFIG mode fail2\r\n");
		return -1;
	}
		
		return 1;
}

void cmd_wifi_list(void)
{
	u32 i=0,AP_cnt;
	s32     pairwise_cipher_index=0,group_cipher_index=0;
	u8      sec_str[][7]= {"OPEN","WEP40","WEP104","TKIP","CCMP"};
	u8  ssid_buf[MAX_SSID_LEN+1]= {0};
	Ap_sta_status connected_info;
	
	struct ssv6xxx_ieee80211_bss *ap_list = NULL;
	AP_cnt = ssv6xxx_get_aplist_info((void *)&ap_list);
	
	
	MEMSET(&connected_info , 0 , sizeof(Ap_sta_status));
	ssv6xxx_wifi_status(&connected_info);
	
	if((ap_list==NULL) || (AP_cnt==0))
	{
		LOG_PRINTF("AP list empty!\r\n");
		return;
	}
	for (i=0; i<AP_cnt; i++)
	{
	
		if(ap_list[i].channel_id!= 0)
		{
			LOG_PRINTF("BSSID: %02x:%02x:%02x:%02x:%02x:%02x\r\n",
					ap_list[i].bssid.addr[0],  ap_list[i].bssid.addr[1], ap_list[i].bssid.addr[2],  ap_list[i].bssid.addr[3],  ap_list[i].bssid.addr[4],  ap_list[i].bssid.addr[5]);
			MEMSET((void*)ssid_buf,0,sizeof(ssid_buf));
			MEMCPY((void*)ssid_buf,(void*)ap_list[i].ssid.ssid,ap_list[i].ssid.ssid_len);
			LOG_PRINTF("SSID: %s\t", ssid_buf);
			LOG_PRINTF("@Channel Idx: %d\r\n", ap_list[i].channel_id);
			if(ap_list[i].capab_info&BIT(4)) {
				LOG_PRINTF("Secure Type=[%s]\r\n",
						ap_list[i].proto&WPA_PROTO_WPA?"WPA":
						ap_list[i].proto&WPA_PROTO_RSN?"WPA2":"WEP");
	
				if(ap_list[i].pairwise_cipher[0]) {
					pairwise_cipher_index=0;
					LOG_PRINTF("Pairwise cipher=");
					for(pairwise_cipher_index=0; pairwise_cipher_index<8; pairwise_cipher_index++) {
						if(ap_list[i].pairwise_cipher[0]&BIT(pairwise_cipher_index)) {
							LOG_PRINTF("[%s] ",sec_str[pairwise_cipher_index]);
						}
					}
					LOG_PRINTF("\r\n");
				}
				if(ap_list[i].group_cipher) {
					group_cipher_index=0;
					LOG_PRINTF("Group cipher=");
					for(group_cipher_index=0; group_cipher_index<8; group_cipher_index++) {
						if(ap_list[i].group_cipher&BIT(group_cipher_index)) {
							LOG_PRINTF("[%s] ",sec_str[group_cipher_index]);
						}
					}
					LOG_PRINTF("\r\n");
				}
			} else {
				LOG_PRINTF("Secure Type=[NONE]\r\n");
			}
	
			if(!memcmp((void *)ap_list[i].bssid.addr,(void *)connected_info.u.station.apinfo.Mac,ETHER_ADDR_LEN)) {
				LOG_PRINTF("RSSI=-%d (dBm)\r\n",ssv6xxx_get_rssi_by_mac((u8 *)ap_list[i].bssid.addr));
			}
			else {
				LOG_PRINTF("RSSI=-%d (dBm)\r\n",ap_list[i].rxphypad.rpci);
			}
			LOG_PRINTF("\r\n");
		}
	
	}
	FREE((void *)ap_list);
}

void cmd_wifi_scan (void)
{
	netmgr_wifi_scan_async(0xffff, NULL, 0);
}

void cmd_wifi_leave(void)
{
	int ret = -1;
	ret = netmgr_wifi_leave_async();
	if (ret != 0)
	{
		LOG_PRINTF("netmgr_wifi_leave failed !!\r\n");
	}
}


void cmd_wifi_join(void)
{
	int ret = -1;
	wifi_sta_join_cfg *join_cfg = NULL;
	
	join_cfg = (wifi_sta_join_cfg *)MALLOC(sizeof(wifi_sta_join_cfg));
	
	memset(join_cfg,0,sizeof(wifi_sta_join_cfg));
//	memcpy(join_cfg->ssid.ssid, "HUAWEI8201",10);
//	join_cfg->ssid.ssid_len=11;
//	  memcpy(join_cfg->password, "12345678",8);
	
	memcpy(join_cfg->ssid.ssid, "TP-LINK_peter",13);
	join_cfg->ssid.ssid_len=13;
	memcpy(join_cfg->password, "zcm123456",9);

//	memcpy(join_cfg->ssid.ssid, "WIFI-09EFCC",11);
//	join_cfg->ssid.ssid_len=11;
//	memcpy(join_cfg->password, "qwertyu12345",12);
	
//	memcpy(join_cfg->ssid.ssid, "MV-Wireless4",12);
//	join_cfg->ssid.ssid_len=12;
//	memcpy(join_cfg->password, "1qaz2wsx",8);

	ret = netmgr_wifi_join_async(join_cfg);
	if (ret != 0)
	{
		LOG_PRINTF("netmgr_wifi_join_async failed !!\r\n");
	}

	FREE(join_cfg);

}

int16_t netif_status_get()
{
	struct netif *netif;
	
	netif = netif_find(WLAN_IFNAME);
	if (netif)
	{
		return netif_is_up(netif);
	}
		return 0;
}
