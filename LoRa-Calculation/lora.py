#! venv/bin/python

import argparse
import numpy as np
from link_budget import *
import constants
def lora_airtime_calc(
    bandwidth: float,
    spreading_factor: int,
    coding_rate: int,
    payload_length: int,
    preamble_length: int,
    implicit_header: int,
    low_data_rate_optimize: int,
    crc_on: int,
):
    """
    This function calculates a LoRa signal air time in Seconds

    Args:
    ------------
    bandwidth: float
        bandwidth of the signal in Hz
    spreading_factor: int
        spreading_factor of the signal, a number between 6 - 12
    coding_rate: int
        coding rate of signal, 1 - 4/5 | 2 - 4/6 | 3 - 4/7 | 4 - 4/8
    payload_length: int
        payload data transmitted in Bytes
    preamble_length: int
        premable length
    implicit_header: int
        whether to choose to add an header to the communication or not, 1 - means no header, shorter tranmsition time, 0 - means there's header, longer transmtion time
    low_data_rate_optimize: int
        the IC optimizes and lower the tranmsittion time if it detects low data rate, 0 - disabled, 1 - enabled
    crc_on: int
        1 - crc enabled and adds another data to the tranmsittion to be checked in the recevier

    """
    # Symbol Rate
    rs = bandwidth / pow(2, spreading_factor)
    ts = 1 / rs

    # Premable time
    preamble_time = (preamble_length + 4.25) * ts

    # Payload Time
    n_payload = 8 + np.max(
        np.ceil(
            (
                8 * payload_length
                - 4 * spreading_factor
                + 28
                + 16 * crc_on
                - 20 * implicit_header
            )
            / (4 * (spreading_factor - 2 * low_data_rate_optimize))
            * (coding_rate + 4)
        ),
        0,
    )
    time_payload = n_payload * ts

    total_time = time_payload + preamble_time
    return total_time

parser = argparse.ArgumentParser(description="Enter your LoRa transmission configuration.", formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("--cf", type=float, help="Center Frequnecy of the LoRa signal", required=False, default=False)
parser.add_argument("--bw", type=int, help=f"Bandwidth of the LoRa signal, Options are:\n1 - {7.8e3} Hz\n2 - {10.4e3} Hz\n3 - {15.6e3} Hz\n4 - {20.8e3} Hz\n5 - {31.25e3} Hz\n6 - {41.7e3} Hz\n7 - {62.5e3} Hz\n8 - {125e3} Hz\n9 - {250e3} Hz\n10 - {500e3} Hz", required=True, default=False)
parser.add_argument("--sf", type=int, help="Spreading Factor of the LoRa signal. Options are:\n6\n7\n8\n9\n10\n11\n12",required=True)
parser.add_argument("--payload-length", type=int, help="Bytes to transmit", required=True, default=False)
parser.add_argument("--preamble-length", type=int, help="length of preamble", required=True)
parser.add_argument("--cr", type=int, help="Coding rate of the LoRa signal, Options are:\n1 - 4/5\n2 - 4/6\n3 - 4/7\n4 - 4/8 ", required=False, default=1)
parser.add_argument("--implicit-header", type=bool, help="if true, disables the header in the communication (reduces transmission time)", required=False, default=True)
parser.add_argument("--crc", type=bool, help="Adds CRC Bytes to the communication for Error Detection at receiver", required=False, default=False)

args = parser.parse_args()

if __name__ == "__main__":
    # output air time, and max distance by friis 
    
    sens = receiver_sensitivity(constants.constant_bw[args.bw], constants.constant_sf_snr[args.sf], 4) # Chosen NF of 4dB, could be changed.
    airtime = lora_airtime_calc(
    bandwidth = constants.constant_bw[args.bw],
    spreading_factor = args.sf,
    coding_rate = args.cr,
    payload_length = args.payload_length,
    preamble_length = args.preamble_length,
    implicit_header = args.implicit_header,
    low_data_rate_optimize = 0,
    crc_on = args.crc
    )
    if args.cf:
        max_distance = friis_transmittion_equation(args.cf, 14, 1, 1, False, sens)
        print(f"bw: {constants.constant_bw[args.bw]} Hz\nsf: {args.sf}\nAirtime: {(airtime*1000):.3f} miliseconds\nReceiver Sensitivity: {sens} dBm\nMax Distance: {max_distance} Meters")
    else:
        print(f"bw: {constants.constant_bw[args.bw]} Hz\nsf: {args.sf}\nAirtime: {(airtime*1000):.3f} miliseconds\nReceiver Sensitivity: {sens} dBm")