
#include "config.h"
#include "mss-bus.h"
#include "packet.h"
#include "crc.h"

int keep_master_running;

void mss_run_master (const mss_addr* slaves, int slaves_count) {
    /* set up working environment */
    keep_master_running = 1;

    MssPacket* packet = (MssPacket*) malloc( sizeof(MssPacket) );
    /* Array of BUSes to pre-calculate crc checksums. */
    MssPacket* bus_packet = (MssPacket*) malloc( slaves_count * sizeof(MssPacket) );
    int i;
    for( i = 0; i < MAX_ADDR; ++i ) {
        BusPacket* p = (BusPacket)(bus_packet + i);
        p->slave_addr = slaves[ i ];
        p->packet_type = MSS_BUS;
        CRC_FOR_BUS( p );
    }
    int current_slave = 0;
    
    /* main loop */
    while( keep_master_running ) {
        
        /* Send BUS to current slave. */
        send_mss_packet( bus_packet + current_slave );
    
        /* Wait for NRQ, timeout, or data message. */
        int recv_res = receive_mss_packet( packet, MSS_TIMEOUT );
        if(
            (recv_res != MSS_OK) || (
                (recv_res == MSS_OK) &&
                (( (GenericPacket) packet )->packet_type == MSS_DAT)
            )    
        ) {
            /* Unless DAT is broadcast, we expect an ACK packet to appear. */
            if( ((DataPacket) packet)->dst_addr != BROADCAST_ADDR )
                int recv_res = receive_mss_packet( packet, MSS_TIMEOUT );
        } /* else current slave has nothing to transfer. */
        
        /* Shift to next slave. */
        ++current_slave;
        if( current_slave == slaves_count )
            current_slave = 0;
        
    } /* while */

    /* clean up */
    free( packet );
    free( bus_packet );
}

void mss_stop_master (void)
{
    keep_master_running = 0;
}
