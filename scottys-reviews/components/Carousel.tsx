'use client'
import React, { useState } from 'react';
import Link from 'next/link';
import { Swiper, SwiperSlide } from 'swiper/react';
import { Navigation } from 'swiper/modules';
import 'swiper/css';
import 'swiper/css/navigation';

interface CardItem {
  classId: string;
  difficulty: number;
  href: string;
}

interface CarouselProps {
  items: CardItem[];
}

const Carousel: React.FC<CarouselProps> = ({ items }) => {
  return (
    <div className="max-w-6xl mx-auto">
      <style jsx global>{`
        .swiper-button-next,
        .swiper-button-prev {
          color: white !important;
          background:rgb(162, 175, 149) !important;
          width: 40px !important;
          height: 40px !important;
          border-radius: 50%;
          transition: all 0.3s ease;
        }
        .swiper-button-next:hover,
        .swiper-button-prev:hover {
          background:rgb(119, 128, 111) !important;
          transform: scale(1.1);
        }
        .swiper-button-next::after,
        .swiper-button-prev::after {
          font-size: 20px !important;
        }
      `}</style>
      <Swiper
        modules={[Navigation]}
        spaceBetween={20}
        slidesPerView={5}
        loop={true}
        navigation={true}
        className="py-4"
        centeredSlides={true}
      >
        {items.map((item, index) => (
          <SwiperSlide key={index} className="flex justify-center items-center">
            <Link
              href={item.href}
              className="flex flex-col justify-center items-center bg-[#d6e2ce] text-[#3a2c23] rounded-xl aspect-square shadow-lg hover:shadow-xl transition duration-300 hover:underline"
            >
              <h2 className="text-xl sm:text-3xl font-bold">{item.classId}</h2>
              <p className="text-base sm:text-3xl mt-2">{item.difficulty.toFixed(1)}</p>
            </Link>
          </SwiperSlide>
        ))}
      </Swiper>
    </div>
  );
};

export default Carousel;

