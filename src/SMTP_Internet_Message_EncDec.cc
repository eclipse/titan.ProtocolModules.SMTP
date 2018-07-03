/******************************************************************************
* Copyright (c) 2008, 2014  Ericsson AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v2.0
* which accompanies this distribution, and is available at
* https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
*
* Contributors:
*  Gabor Szalai - initial implementation and initial documentation
******************************************************************************/
//
//  File:     SMTP_Internet_Message_EncDec.cc
//  Rev:      R2B
//  Prodnr:   CNL 113 598

#include "SMTP_Internet_Message_Types.hh"

namespace SMTP__Internet__Message__Types {

void encode_utf8(TTCN_Buffer& buf, const UNIVERSAL_CHARSTRING& uchars )
{
  uchars.encode_utf8(buf);
}

void decode_utf8(int n_octets, const unsigned char *octets_ptr, UNIVERSAL_CHARSTRING& ustring)
{
  ustring.decode_utf8(n_octets,octets_ptr);
}


  Mail__PDU dec__Mail__PDU(const CHARSTRING& stream)
  {
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
      TTCN_Logger::begin_event(TTCN_DEBUG);
      TTCN_Logger::log_event_str("dec_Mail_PDU(): Stream before decoding: ");
      stream.log();
      TTCN_Logger::end_event();
    }
    TTCN_EncDec::set_error_behavior(TTCN_EncDec::ET_ALL, TTCN_EncDec::EB_DEFAULT);
    TTCN_EncDec::clear_error();
    TTCN_Buffer ttcn_buffer;
    int state_=0;
    const char* stream_buff=(const char*)stream;
    for(int k_=0;k_<stream.lengthof();k_++){
      switch(state_){
        case 0:
          if(stream_buff[k_]=='\r'){
            state_=1;
          } else if(stream_buff[k_]==' ' || stream_buff[k_]=='\t'){
            state_=2;
          } else {
            state_=0;
            ttcn_buffer.put_c((const unsigned char)stream_buff[k_]);
          }
          break;
        case 1:
          if(stream_buff[k_]=='\n'){
            state_=1;
          } else if(stream_buff[k_]=='\r'){
            ttcn_buffer.put_s(2,(const unsigned char*)"\r\n");
            state_=3;
          } else if(stream_buff[k_]==' ' || stream_buff[k_]=='\t'){
            state_=2;
          } else {
            state_=0;
            ttcn_buffer.put_s(2,(const unsigned char*)"\r\n");
            ttcn_buffer.put_c((const unsigned char)stream_buff[k_]);
          }
          break;
        case 2:
          if(stream_buff[k_]=='\r'){
            state_=1;
          } else if(stream_buff[k_]==' ' || stream_buff[k_]=='\t'){
            state_=2;
          } else {
            state_=0;
            ttcn_buffer.put_c(' ');
            ttcn_buffer.put_c((const unsigned char)stream_buff[k_]);
          }
          break;
        case 3:
          if(stream_buff[k_]=='\n'){
            state_=3;
          } else {
            ttcn_buffer.put_s(2,(const unsigned char*)"\r\n");
            ttcn_buffer.put_s(stream.lengthof()-k_,(const unsigned char*)(stream_buff+k_));
            k_=stream.lengthof();
          }
          break;
      }
    }
    Mail__PDU ret_val;
// TTCN_EncDec::set_error_behavior(TTCN_EncDec::ET_LOG_MATCHING,TTCN_EncDec::EB_WARNING);
    if(state_ != 3 ){ // there are no mail headers
      ret_val.fields()=OMIT_VALUE;
      ret_val.body()=stream;
    } else  ret_val.decode(Mail__PDU_descr_, ttcn_buffer, TTCN_EncDec::CT_TEXT);
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
      TTCN_Logger::begin_event(TTCN_DEBUG);
      TTCN_Logger::log_event_str("dec_Mail_PDU(): Decoded @SMTP_Internet_Message_Types.Mail_PDU: ");
      ret_val.log();
      TTCN_Logger::end_event();
    }
    return ret_val;
  }


  Mail__PDU__utf8 dec__Mail__PDU__utf8(const OCTETSTRING& stream)
  {
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
      TTCN_Logger::begin_event(TTCN_DEBUG);
      TTCN_Logger::log_event_str("dec_Mail_PDU(): Stream before decoding: ");
      stream.log();
      TTCN_Logger::end_event();
    }
    TTCN_EncDec::set_error_behavior(TTCN_EncDec::ET_ALL, TTCN_EncDec::EB_DEFAULT);
    TTCN_EncDec::clear_error();
    TTCN_Buffer ttcn_buffer;
    int state_=0;
    const unsigned char* stream_buff=(const unsigned char*)stream;
    for(int k_=0;k_<stream.lengthof();k_++){
      switch(state_){
        case 0:
          if(stream_buff[k_]=='\r'){
            state_=1;
          } else if(stream_buff[k_]==' ' || stream_buff[k_]=='\t'){
            state_=2;
          } else {
            state_=0;
            ttcn_buffer.put_c((const unsigned char)stream_buff[k_]);
          }
          break;
        case 1:
          if(stream_buff[k_]=='\n'){
            state_=1;
          } else if(stream_buff[k_]=='\r'){
            ttcn_buffer.put_s(2,(const unsigned char*)"\r\n");
            state_=3;
          } else if(stream_buff[k_]==' ' || stream_buff[k_]=='\t'){
            state_=2;
          } else {
            state_=0;
            ttcn_buffer.put_s(2,(const unsigned char*)"\r\n");
            ttcn_buffer.put_c((const unsigned char)stream_buff[k_]);
          }
          break;
        case 2:
          if(stream_buff[k_]=='\r'){
            state_=1;
          } else if(stream_buff[k_]==' ' || stream_buff[k_]=='\t'){
            state_=2;
          } else {
            state_=0;
            ttcn_buffer.put_c(' ');
            ttcn_buffer.put_c((const unsigned char)stream_buff[k_]);
          }
          break;
        case 3:
          if(stream_buff[k_]=='\n'){
            state_=3;
          } else {
            ttcn_buffer.put_s(2,(const unsigned char*)"\r\n");
            ttcn_buffer.put_s(stream.lengthof()-k_,(const unsigned char*)(stream_buff+k_));
            k_=stream.lengthof();
          }
          break;
      }
    }
    Mail__PDU__utf8 ret_val;
// TTCN_EncDec::set_error_behavior(TTCN_EncDec::ET_LOG_MATCHING,TTCN_EncDec::EB_WARNING);
    if(state_ != 3 ){ // there are no mail headers
      ret_val.fields()=OMIT_VALUE;
      decode_utf8(stream.lengthof(), (const unsigned char*)stream, ret_val.body());
    } else {
      ret_val.fields()().decode(Mail__Headers_descr_, ttcn_buffer, TTCN_EncDec::CT_TEXT);
      decode_utf8(ttcn_buffer.get_read_len()-1, ttcn_buffer.get_read_data(), ret_val.body());
    } 
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
      TTCN_Logger::begin_event(TTCN_DEBUG);
      TTCN_Logger::log_event_str("dec_Mail_PDU(): Decoded @SMTP_Internet_Message_Types.Mail_PDU: ");
      ret_val.log();
      TTCN_Logger::end_event();
    }
    return ret_val;
  }

OCTETSTRING enc__Mail__PDU__utf8(const Mail__PDU__utf8& pdu)
{
// written by generate_code_encode in AST_ttcn3.cc at 5571
  if (TTCN_Logger::log_this_event(TTCN_Logger::DEBUG_ENCDEC)) {
    TTCN_Logger::begin_event(TTCN_Logger::DEBUG_ENCDEC);
    TTCN_Logger::log_event_str("enc_Mail_PDU(): Encoding @SMTP_Internet_Message_Types.Mail_PDU: ");
    pdu.log();
    TTCN_Logger::end_event();
  }
  TTCN_EncDec::set_error_behavior(TTCN_EncDec::ET_ALL, TTCN_EncDec::EB_DEFAULT);
  TTCN_Buffer ttcn_buffer;
  if(pdu.fields().ispresent()){
    pdu.fields()().encode(Mail__Headers_descr_, ttcn_buffer, TTCN_EncDec::CT_TEXT);
  }
  encode_utf8(ttcn_buffer, pdu.body() );
  OCTETSTRING ret_val;
  ttcn_buffer.get_string(ret_val);

  if (TTCN_Logger::log_this_event(TTCN_Logger::DEBUG_ENCDEC)) {
    TTCN_Logger::begin_event(TTCN_Logger::DEBUG_ENCDEC);
    TTCN_Logger::log_event_str("enc_Mail_PDU(): Stream after encoding: ");
    ret_val.log();
    TTCN_Logger::end_event();
  }
  return ret_val;
}


}
