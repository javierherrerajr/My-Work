// app/review/page.tsx
import React, { Suspense } from "react";
import { ReviewFormWrapper } from "@/components/ReviewFormWrapper";
import Header from "@/components/Header";
import Footer from '@/components/Footer';
import { prisma } from "@/lib/prisma";

export default async function ReviewPage() {
  try {
    const courses = await prisma.class.findMany({
      orderBy: {
        classname: 'asc'
      }
    });
    
    return (
      <>
        <Header />
        <div className="max-w-xl mx-auto p-4 pt-10">
          <h1 className="text-2xl font-fredoka font-semibold mb-4 text-center pt-5">Leave a Review!</h1>
          <Suspense fallback={<div className="text-center">Loading courses...</div>}>
            <ReviewFormWrapper courses={courses} />
          </Suspense>
        </div>
        <div className="mt-8">
          <Footer />
        </div>
      </>
    );
  } catch (error) {
    console.error('Error loading courses:', error);
    return (
      <>
        <Header />
        <div className="max-w-xl mx-auto p-4 pt-10">
          <div className="text-red-500 text-center">
            Failed to load courses. Please try again later.
          </div>
        </div>
        <div className="mt-8">
          <Footer />
        </div>
      </>
    );
  }
}