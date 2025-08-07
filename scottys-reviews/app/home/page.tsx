'use client'

import '@/styles/globals.css'
import Image from 'next/image'
import { SearchBar } from '@/components/SearchBar'
import Header from '@/components/Header'
import { Button } from '@/components/ui/button'
import Carousel from '@/components/Carousel'
import Link from 'next/link'

import Footer from '@/components/Footer'
import { styled } from 'styled-components'

const PageWrapper = styled.div`
  display: flex;
  flex-direction: column;
  min-height: 100vh;
`;

const Content = styled.main`
  flex: 1;
`;

export default function HomePage() {
    return (
        <>
            {/* header section*/}
            <Header />

            {/* search bar section*/}
            <div className="pt-[100px]">
                <h1 className="text-[45px] text-center font-fredoka font-black font-extrabold pt-5 font-bold">
                    Search for your classes!
                </h1>
                <div className="flex justify-center focus:outline-none font-fredoka py-10">
                    <SearchBar />
                </div>
            </div>
            {/* gallery section*/}
            <div className=" justify-center full-width relative mt-[150px] ">
               
                <Image
                    src="/gallery.svg"
                    alt="gallery"
                    width={1920}
                    height={1000}
                />
                <h1 className="absolute top-[150px] left-1/2 transform -translate-x-1/2 text-center text-[45px] font-fredoka font-black font-extrabold z-10"> UCR's Most Pawsitive Classes </h1>
                {/* can only be odd number of classes must be greater than 5 items */}
                <div className="absolute inset-0 top-[50px] flex items-center justify-center z-10">
                    <Carousel
                        items={[
                            { classId: 'CS 010C', difficulty: 7.2, href: '/courses/CS010C' },
                            { classId: 'CS 111', difficulty: 8.0, href: '/courses/CS111' },
                            { classId: 'AHS021', difficulty: 2.5, href: '/courses/AHS021' },
                            { classId: 'BIOL002', difficulty: 2.7, href: '/courses/BIOL002' },
                            { classId: 'HIST010', difficulty: 4.4, href: '/courses/HIST010' },
                            { classId: 'BUS101', difficulty: 4.3, href: '/courses/BUS101' },
                            { classId: 'DNCE012', difficulty: 1.0, href: '/courses/DNCE012' },
                            { classId: 'CS 100', difficulty: 6.8, href: '/courses/CS100' },
                            { classId: 'EDUC042', difficulty: 2.0, href: '/courses/EDUC042' },
                            { classId: 'SOC001', difficulty: 5.2, href: '/courses/SOC001' },
                        ]}
                    />
                </div>
            </div>
            {/* bottom */}
            <div className="py-12 px-20 full-width max-w-[3000px] mx-auto">
            <Image
            src="/informational.svg"
            alt="informational"
            width={1339}
            height={1336}
            className='w-full h-full'
            /> 
            </div> 
            {/* footer section*/}
            <Footer />

            
        </>
    )
}