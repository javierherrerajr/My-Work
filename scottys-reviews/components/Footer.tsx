"use client";
import styled from 'styled-components';

const StyledFooter = styled.footer`
  width: 100vw;
  height: 100px;
  overflow: hidden;
  margin: 0;
  padding: 0;
  width: 100vw;
  position: relative;
  left: 50%;
  right: 50%;
  margin-left: -50vw;
  margin-right: -50vw;
  margin-top: auto;
`;

const FooterSVG = styled.svg`
  width: 100vw;
  height: 110px;
  display: block;
`;

const Footer: React.FC = () => {
  return (
    <StyledFooter>
      <FooterSVG viewBox="0 -20 700 110" preserveAspectRatio="none">
        <path transform="translate(0, -20)" d="M0,10 c80,-22 240,0 350,18 c90,17 260,7.5 350,-20 v50 h-700" fill="#D3DFC7" />
        <path d="M0,10 c80,-18 230,-12 350,7 c80,13 260,17 350,-5 v100 h-700z" fill="#B0C69A" />
      </FooterSVG>
    </StyledFooter>
  );
};

export default Footer;

